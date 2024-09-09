/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:28:58 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 12:16:42 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char **input)
{
	while ((**input >= 9 && **input <= 13) || **input == 32)
		(*input)++;
}

bool	is_separator(char **str, char quote_char)
{
	char	current;
	char	next;

	current = **str;
	next = *(*str + 1);
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

int	allocate_memory_for_token(char *input)
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

int	find_key_length(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '?')
			return (-1);
		i++;
	}
	return ((str[i] == '=') ? i : 0);
}
