/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:48 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 12:45:29 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	determine_length_helper(char **line, char delimiter)
{
	int	number;

	number = 0;
	if (is_dollar_sequence(line) != 0)
		return (2);
	if (**line == 36 && ignore_chars(line, NULL))
		number++;
	while (**line && **line != delimiter && is_delimiter(**line) == false)
	{
		(*line)++;
		number++;
	}
	return (number);
}

int	determine_length(char *line, char delimiter)
{
	int	number;
	int	b;

	b = 0;
	number = 0;
	if ((*line == 39 || *line == 34) && ignore_chars(&line,
			&number) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (*line == delimiter)
	{
		while (*line++ == delimiter)
			number++;
	}
	else
		number += determine_length_helper(&line, delimiter);
	return (number);
}
