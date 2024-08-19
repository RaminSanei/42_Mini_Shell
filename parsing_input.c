/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/19 17:06:56 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(const char *str)
{
	char	quote_char;

	while (*str == 32 || *str == 9 || 11 <= *str <= 13)
		str++;
	quote_char = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			quote_char = *str;
			str++;
			while (*str && *str != quote_char)
				str++;
			if (*str == '\0')
			{
				fprintf(stderr, ERROR_OPEN_QUOTE);
				return (EXIT_FAILURE);
			}
		}
		str++;
	}
	return (EXIT_SUCCESS);
}

int	parsing_input(t_mini *shell)
{
	if (check_unclosed_quotes(shell->line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
