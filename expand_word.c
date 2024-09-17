/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:56:04 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:00:10 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*non_qts(t_mini *shell, char **actions, int *index)
{
	char	*result;
	char	*expanded_action;
	char	*temp;

	result = NULL;
	while (actions[*index] && ft_strcmp(actions[*index], "\"")
		&& ft_strcmp(actions[*index], "\'"))
	{
		expanded_action = expand_action(shell, actions[*index]);
		if (result)
		{
			temp = result;
			result = ft_strjoin(temp, expanded_action);
			free(temp);
		}
		else
		{
			result = expanded_action;
		}
		(*index)++;
	}
	return (result);
}

char	*double_qts(t_mini *shell, char **actions, int *index)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(actions[*index], "\"") && actions[*index])
		(*index)++;
	while (ft_strcmp(actions[*index], "\"") && actions[*index])
	{
		if (ft_strchr(actions[*index], '$'))
			result = ft_strnjoin(result, retrieve_inf_value(shell,
						actions[*index] + 1), 2);
		else
			result = ft_strnjoin(result, actions[*index], 1);
		(*index)++;
	}
	if (!ft_strcmp(actions[*index], "\"") && actions[*index])
		(*index)++;
	return (result);
}

char	*single_qts(char **actions, int *index)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(actions[*index], "\'") && actions[*index])
		(*index)++;
	while (ft_strcmp(actions[*index], "\'") && actions[*index])
	{
		result = ft_strnjoin(result, actions[*index], 1);
		(*index)++;
	}
	if (!ft_strcmp(actions[*index], "\'") && actions[*index])
		(*index)++;
	return (result);
}

void	expand_word(t_mini *shell, t_list *elem, char **arguments, int *index)
{
	if (!ft_strcmp(arguments[*index], "\""))
		elem->content = ft_strnjoin(elem->content, double_qts(shell, arguments,
					index), 2);
	else if (!ft_strcmp(arguments[*index], "\'"))
		elem->content = ft_strnjoin(elem->content, single_qts(arguments, index),
				2);
	else
		elem->content = ft_strnjoin(elem->content, non_qts(shell, arguments,
					index), 2);
}
