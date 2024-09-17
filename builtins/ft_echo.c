/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:23 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:31:24 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	all_chars_valid(const char *line, char c)
{
	int	k;

	if (line[0] != '-')
		return (false);
	k = 1;
	while (line[k] != '\0')
	{
		if (line[k] != c)
			return (false);
		k++;
	}
	return (true);
}

static char	*concat_with_delim(char *line, const char *to_add)
{
	char	*new_str;
	size_t	str_len;
	size_t	add_len;

	str_len = 0;
	add_len = strlen(to_add);
	if (line)
		str_len = strlen(line);
	new_str = safe_malloc(str_len + add_len + 1);
	if (line)
		memcpy(new_str, line, str_len);
	memcpy(new_str + str_len, to_add, add_len + 1);
	return (new_str);
}

char	*join_strings(char *args[])
{
	char	*line;
	bool	parsed_line;
	int		j;

	line = NULL;
	j = 1;
	parsed_line = false;
	if (args[j] && all_chars_valid(args[j], 'n'))
	{
		parsed_line = !parsed_line;
		j++;
	}
	if (!args[j])
		return (strdup(""));
	while (args[j])
	{
		line = concat_with_delim(line, args[j]);
		if (args[j + 1])
			line = concat_with_delim(line, " ");
		j++;
	}
	if (!parsed_line)
		line = concat_with_delim(line, "\n");
	return (line);
}

static char	*concatenate_args(char *args[])
{
	char	*result;

	result = join_strings(args);
	return (result);
}

int	built_echo(t_mini *shell, char *argv[])
{
	char	*line;

	line = concatenate_args(argv);
	if (!line)
		return (MINUS1);
	printf("%s", line);
	free(line);
	(void)shell;
	return (EXIT_SUCCESS);
}
