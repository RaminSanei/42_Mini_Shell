/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:21:52 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_action(char **input, int index)
{
	char	*action;
	char	quote_char;

	quote_char = 0;
	action = (char *)safe_malloc(allocate_memory_for_action(*input) + 1);
	while (**input)
	{
		if (**input == 34 || **input == 39)
		{
			if (**input == quote_char)
				quote_char = 0;
			else if (quote_char == 0)
				quote_char = **input;
		}
		action[index++] = **input;
		if (**input == 0 || is_separator(input, quote_char))
			break ;
		(*input)++;
	}
	action[index] = 0;
	return (action);
}

void	assign_action_type(t_list **action_list)
{
	t_list	*current_action;

	if (!action_list || !*action_list)
		return ;
	current_action = *action_list;
	while (current_action->f_ward)
		current_action = current_action->f_ward;
	if (are_strings_equal(current_action->content, ""))
		current_action->kind = EMPTY;
	else if (are_strings_equal(current_action->content, ">"))
		current_action->kind = TRUNC;
	else if (are_strings_equal(current_action->content, "|"))
		current_action->kind = PIPE;
	else if (are_strings_equal(current_action->content, "<"))
		current_action->kind = INPUT;
	else if (are_strings_equal(current_action->content, "<<"))
		current_action->kind = HEREDOC;
	else if (are_strings_equal(current_action->content, ">>"))
		current_action->kind = APPEND;
	else if (!current_action->b_ward || current_action->b_ward->kind == PIPE
		|| (current_action->b_ward->b_ward
			&& current_action->b_ward->b_ward->kind == HEREDOC))
		current_action->kind = CMD;
	else
		current_action->kind = ARG;
}

void	insert_action_to_list(t_list **action_list, char *current_action)
{
	t_list	*new_action;
	t_list	*current;

	new_action = (t_list *)safe_malloc(sizeof(t_list));
	new_action->content = ft_strdup(current_action);
	if (!new_action->content)
	{
		free(new_action);
		return ;
	}
	new_action->f_ward = NULL;
	new_action->b_ward = NULL;
	if (!*action_list)
		*action_list = new_action;
	else
	{
		current = *action_list;
		while (current->f_ward)
			current = current->f_ward;
		current->f_ward = new_action;
		new_action->b_ward = current;
	}
}

t_list	*generate_actions(char **input)
{
	t_list	*action_list;
	char	*current_action;
	int		index;

	index = 0;
	current_action = NULL;
	action_list = NULL;
	while (**input)
	{
		skip_whitespace(input);
		if (*(*input) == '\0')
			break ;
		current_action = extract_action(input, index);
		insert_action_to_list(&action_list, current_action);
		assign_action_type(&action_list);
		free(current_action);
		if (*(*input) == '\0')
			break ;
		(*input)++;
		skip_whitespace(input);
	}
	return (action_list);
}
