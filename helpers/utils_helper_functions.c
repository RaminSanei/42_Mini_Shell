/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:48 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:36:58 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_delimiter(char c)
{
	if (c == 34)
		return (true);
	else if (c == 36)
		return (true);
	else if (c == 39)
		return (true);
	return (false);
}

int	ignore_chars(char **line, int *number)
{
	if (*(*line - 1) && *(*line - 1) == 32)
		*number += 1;
	if (*(*line) != 0)
	{
		(*line)++;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	parse_symbol_pairs(int *number, char **line)
{
	while (**line == 36 && *(*line + 1) == 36)
	{
		(*number)++;
		(*line) += 2;
	}
}

void	cleanup_string_list(char **string_array, int num_elements)
{
	int	k;

	k = 0;
	if (!string_array)
		return ;
	while (k++ < num_elements)
		free(string_array[k]);
	free(string_array);
}

bool	is_dollar_sequence(char **line)
{
	if (**line == 36 && *(*line + 1) == 36)
	{
		*line += 2;
		return (true);
	}
	return (false);
}
