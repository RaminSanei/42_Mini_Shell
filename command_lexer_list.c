/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/31 18:58:59 by ssanei           ###   ########.fr       */
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
		append_command(&command_list, lexer, arguments);
		if (toks)
			toks = toks->next;
	}
	return (command_list);
}
