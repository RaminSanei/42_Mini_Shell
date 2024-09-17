/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:51:46 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:18:25 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*construct_full_address_helper(const char *adr_element,
		const char *action, int adr_len, int ac_len)
{
	char	*final_address;

	final_address = safe_malloc(adr_len + ac_len + 2);
	ft_strlcpy(final_address, adr_element, adr_len + 1);
	ft_strlcpy(final_address + adr_len, "/", 2);
	ft_strlcpy(final_address + adr_len + 1, action, ac_len + 1);
	return (final_address);
}

char	*handle_special_cases(const char *key, int drop_num)
{
	if (*key == '\0')
		return (ft_strdup("$"));
	else if (*key == '$')
		return (ft_itoa(getpid()));
	else if (*key == '?')
		return (ft_itoa(drop_num));
	return (NULL);
}

bool	check_unclosed_quotes(const char *line)
{
	char	quote_char;

	while (*line == 32 || *line == 9 || (11 <= *line && *line <= 13))
		line++;
	quote_char = 0;
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
		{
			quote_char = *line;
			line++;
			while (*line && *line != quote_char)
				line++;
			if (*line == '\0')
			{
				fprintf(stderr, ERROR_OPEN_QUOTE);
				return (true);
			}
		}
		line++;
	}
	return (false);
}

int	check_redirection_syntax(t_list *elem)
{
	if ((elem->kind == APPEND || elem->kind == INPUT
			|| elem->kind == TRUNC || elem->kind == HEREDOC) && (!elem->f_ward
			|| elem->f_ward->kind > ARG))
		return (ERROR_UNEXPECTED_NEWLINE);
	return (EXIT_SUCCESS);
}
