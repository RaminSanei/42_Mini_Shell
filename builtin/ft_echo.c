/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:23 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 13:24:40 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	isall_char(const char *str, char c)
{
	int	i;

	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

static char	*concat_with_delim(char *str, const char *to_add, int free_str)
{
	char	*new_str;
	size_t	str_len;
	size_t	add_len;

	str_len = (str) ? strlen(str) : 0;
	add_len = strlen(to_add);
	new_str = malloc(str_len + add_len + 1);
	if (!new_str)
		return (NULL);
	if (str)
	{
		memcpy(new_str, str, str_len);
		free(str);
	}
	memcpy(new_str + str_len, to_add, add_len + 1);
	return (new_str);
}

char	*ft_cat(char **argv)
{
	char	*str;
	int		i;
	int		new_line;

	str = NULL;
	i = 1;
	new_line = 1;
	if (argv[i] && ft_isall_char(argv[i], 'n'))
	{
		new_line = 0;
		i++;
	}
	if (!argv[i])
		return (strdup(""));
	while (argv[i])
	{
		str = concat_with_delim(str, argv[i], 0);
		if (argv[i + 1])
			str = concat_with_delim(str, " ", 1);
		i++;
	}
	if (new_line)
		str = concat_with_delim(str, "\n", 1);
	return (str);
}

//////////////////////echo////////////////////////

static char	*concatenate_args(char **argv)
{
	char	*result;

	result = ft_cat(argv);
	return (result);
}

int	echo(char *argv[], t_mini *obj)
{
	char	*str;

	(void)obj;
	str = concatenate_args(argv);
	if (!str)
		return (MINUS1);
	printf("%s", str);
	free(str);
	return (EXIT_SUCCESS);
}
