/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_scanner_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:37:44 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_list *elem)
{
	int	count;

	count = 0;
	while (elem && elem->kind != PIPE)
	{
		if (elem->kind == CMD || elem->kind == EMPTY || elem->kind == ARG)
			count++;
		elem = elem->f_ward;
	}
	return (count);
}

char	**allocate_arguments(t_list *elem)
{
	int		argument_count;
	char	**arguments;

	argument_count = count_arguments(elem);
	arguments = (char **)safe_malloc(sizeof(char *) * (argument_count + 1));
	arguments[argument_count] = NULL;
	return (arguments);
}
