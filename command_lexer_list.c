/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/05 16:36:53 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_list *toks)
{
	int	count;

	count = 0;
	while (toks && toks->t_type != PIPE)
	{
		if (toks->t_type == CMD || toks->t_type == EMPTY || toks->t_type == ARG)
			count++;
		toks = toks->next;
	}
	return (count);
}

void	add_lexer_to_list(t_list_l **lexer_list, const char *str, int type)
{
	t_list_l	*new_node;
	t_list_l	*current_node;

	new_node = (t_list_l *)malloc(sizeof(t_list_l));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(str);
	new_node->type = type;
	new_node->next = NULL;
	if (!*lexer_list)
	{
		*lexer_list = new_node;
		return ;
	}
	current_node = *lexer_list;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = new_node;
}

void	handle_redirection(t_list_l **lexer_list, t_list **current_token)
{
	if (!current_token || !(*current_token) || !(*current_token)->next)
		return ;
	add_lexer_to_list(lexer_list, (*current_token)->next->content,
		(*current_token)->t_type);
	*current_token = (*current_token)->next;
}

void	parse_tokens_for_redirection(t_list **token, t_list_l **lexer)
{
	while (*token && (*token)->t_type != PIPE)
	{
		if ((*token)->t_type == APPEND || (*token)->t_type == INPUT
			|| (*token)->t_type == TRUNC || (*token)->t_type == HEREDOC)
			handle_redirection(lexer, token);
		*token = (*token)->next;
	}
}

void	parse_tokens_to_arguments(t_list **token, char **arguments)
{
	int	i;

	i = 0;
	while (*token && (*token)->t_type != PIPE)
	{
		if ((*token)->t_type == CMD || (*token)->t_type == EMPTY
			|| (*token)->t_type == ARG)
			arguments[i++] = ft_strdup((*token)->content);
		*token = (*token)->next;
	}
}

char	**allocate_arguments(t_list *toks)
{
	int		argument_count;
	char	**arguments;

	argument_count = count_arguments(toks);
	arguments = (char **)malloc(sizeof(char *) * (argument_count + 1));
	if (!arguments)
		return (NULL);
	arguments[argument_count] = NULL;
	return (arguments);
}

void	add_command_to_list(t_list_c **cmd_list, t_list_l *lexer_data,
		char **argv_data)
{
	t_list_c	*new_cmd;
	t_list_c	*current;

	new_cmd = (t_list_c *)malloc(sizeof(t_list_c));
	if (!new_cmd)
		return ;
	new_cmd->content = argv_data;
	new_cmd->lexer = lexer_data;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
	}
	else
	{
		current = *cmd_list;
		while (current->next)
			current = current->next;
		current->next = new_cmd;
		new_cmd->prev = current;
	}
}

t_list_c	*build_command_list(t_list *toks)
{
	t_list_c	*command_list;
	t_list_l	*lexer;
	char		**arguments;

	command_list = NULL;
	while (toks)
	{
		lexer = NULL;
		arguments = allocate_arguments(toks);
		parse_tokens_to_arguments(&toks, arguments);
		parse_tokens_for_redirection(&toks, &lexer);
		add_command_to_list(&command_list, lexer, arguments);
		if (toks)
			toks = toks->next;
	}
	return (command_list);
}
