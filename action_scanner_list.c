/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_scanner_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:43:41 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_scanner_to_list(t_list_l **scanner_list, char *line, int type)
{
	t_list_l	*new_node;
	t_list_l	*current_node;

	new_node = (t_list_l *)safe_malloc(sizeof(t_list_l));
	new_node->content = ft_strdup(line);
	new_node->type = type;
	new_node->f_ward = NULL;
	if (!*scanner_list)
	{
		*scanner_list = new_node;
		return ;
	}
	current_node = *scanner_list;
	while (current_node->f_ward)
		current_node = current_node->f_ward;
	current_node->f_ward = new_node;
}

void	handle_redirection(t_list_l **scanner_list, t_list **current_token)
{
	if (!current_token || !(*current_token) || !(*current_token)->f_ward)
		return ;
	if ((*current_token) && (*current_token)->f_ward)
	{
		add_scanner_to_list(scanner_list, (*current_token)->f_ward->content,
			(*current_token)->kind);
		*current_token = (*current_token)->f_ward;
	}
}

void	parse_actions_to_arguments(t_list **action, char **arguments,
		t_list_l **scanner)
{
	int	k;

	k = 0;
	while (*action && (*action)->kind != PIPE)
	{
		if ((*action) && ((*action)->kind == CMD || (*action)->kind == EMPTY
				|| (*action)->kind == ARG))
		{
			arguments[k] = ft_strdup((*action)->content);
			k++;
		}
		else if ((*action) && ((*action)->kind == APPEND
				|| (*action)->kind == INPUT || (*action)->kind == TRUNC
				|| (*action)->kind == HEREDOC))
		{
			handle_redirection(scanner, action);
		}
		*action = (*action)->f_ward;
	}
}

void	add_action_to_list(t_list_c **act_list, t_list_l *scanner_data,
		char **argv_data)
{
	t_list_c	*new_act;
	t_list_c	*current;

	new_act = (t_list_c *)safe_malloc(sizeof(t_list_c));
	new_act->content = argv_data;
	new_act->scanner = scanner_data;
	new_act->f_ward = NULL;
	new_act->b_ward = NULL;
	if (!*act_list)
	{
		*act_list = new_act;
	}
	else
	{
		current = *act_list;
		while (current->f_ward)
			current = current->f_ward;
		current->f_ward = new_act;
		new_act->b_ward = current;
	}
}

t_list_c	*build_action_list(t_list *elem)
{
	t_list_c	*action_list;
	char		**arguments;
	t_list_l	*scanner;

	action_list = NULL;
	while (elem)
	{
		scanner = NULL;
		arguments = allocate_arguments(elem);
		parse_actions_to_arguments(&elem, arguments, &scanner);
		add_action_to_list(&action_list, scanner, arguments);
		if (elem)
			elem = elem->f_ward;
	}
	return (action_list);
}
