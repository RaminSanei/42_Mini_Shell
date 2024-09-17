/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:28:58 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:27:50 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char **input)
{
	while ((**input >= 9 && **input <= 13) || **input == 32)
		(*input)++;
}

bool	is_separator(char **line, char quote_char)
{
	char	current;
	char	next;

	current = **line;
	next = *(*line + 1);
	if (quote_char != 0)
		return (false);
	if (current == 62 || current == 60)
	{
		if (next == current)
			return (false);
		return (true);
	}
	if (current == 32 || current == 124)
		return (true);
	if (next == 32 || next == 124 || next == 62 || next == 60)
		return (true);
	return (false);
}

int	allocate_memory_for_action(char *input)
{
	int		index;
	char	quote_char;

	index = 0;
	quote_char = 0;
	while (*input)
	{
		if (*input == 34 || *input == 39)
		{
			if (*input == quote_char)
				quote_char = 0;
			else if (quote_char == 0)
				quote_char = *input;
		}
		index++;
		if (*input == 0 || is_separator(&input, quote_char))
			break ;
		input++;
	}
	return (index);
}

int	find_key_length(const char *line)
{
	int	k;

	k = 0;
	while (line[k] && line[k] != 61)
	{
		if (line[k] == 32 || line[k] == 63)
			return (MINUS1);
		k++;
	}
	if (line[k] == 61)
		return (k);
	else
		return (0);
}

void	erase_pointer_array(char **array)
{
	int	k;

	k = -1;
	while (array[++k])
		free(array[k]);
	free(array);
}
