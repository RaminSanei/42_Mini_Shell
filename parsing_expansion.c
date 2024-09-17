/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:02:50 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 15:56:29 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lookup_inf_variable(t_list_e *inf_list, const char *key)
{
	char	*value;
	int		key_length;
	int		key_equal_length;

	value = NULL;
	key_length = ft_strlen(key);
	while (inf_list)
	{
		key_equal_length = find_key_length(inf_list->content);
		if (ft_strncmp(key, inf_list->content, key_length) == 0
			&& ft_strncmp(inf_list->content, key, key_equal_length) == 0)
		{
			value = ft_strdup(ft_strchr(inf_list->content, '=') + 1);
			break ;
		}
		inf_list = inf_list->f_ward;
	}
	return (value);
}

char	*retrieve_inf_value(t_mini *shell, const char *key)
{
	char	*result;

	result = handle_special_cases(key, shell->drop_num);
	if (result != NULL)
		return (result);
	result = lookup_inf_variable(shell->inf, key);
	if (result != NULL)
		return (result);
	return (ft_strdup(""));
}

char	*expand_action(t_mini *shell, char *action)
{
	if (ft_strchr(action, '$'))
		return (ft_strnjoin(NULL, retrieve_inf_value(shell, action + 1), 2));
	return (ft_strdup(action));
}

void	process_action(t_mini *shell, t_list *elem)
{
	char	**split_actions;
	int		index;

	split_actions = ft_split(elem->content, ' ');
	free(elem->content);
	elem->content = NULL;
	index = 0;
	while (split_actions[index])
	{
		expand_word(shell, elem, split_actions, &index);
	}
	erase_pointer_array(split_actions);
}

void	perform_expansion(t_mini *shell)
{
	t_list	*current_action;

	current_action = shell->elem;
	while (current_action)
	{
		process_action(shell, current_action);
		current_action = current_action->f_ward;
	}
}
