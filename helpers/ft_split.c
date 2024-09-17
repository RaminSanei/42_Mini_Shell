/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:07:48 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:00:57 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	compute_text_length_helper(int *number, char **line, char delimiter)
{
	if (**line == delimiter || **line == 39 || **line == 34)
	{
		while (**line == delimiter)
			(*line)++;
		ignore_chars(line, number);
		(*number)++;
	}
	else if (**line)
	{
		parse_symbol_pairs(number, line);
		if (**line == 36)
			ignore_chars(line, number);
		while (**line && **line != delimiter && is_delimiter(**line) == false)
			(*line)++;
		(*number)++;
	}
}

int	compute_text_length(char *line, char delimiter)
{
	int	b;
	int	number;

	b = 0;
	number = 0;
	while (*line)
		compute_text_length_helper(&number, &line, delimiter);
	return (number);
}

char	**ft_split(char *line, char delimiter)
{
	int		element_count;
	char	**line_list;
	int		element_length;
	int		k;

	element_count = compute_text_length(line, delimiter);
	line_list = (char **)safe_malloc((element_count + 1) * sizeof(char *));
	k = 0;
	while (k < element_count)
	{
		element_length = determine_length(line, delimiter);
		line_list[k] = (char *)malloc(element_length + 1);
		if (!line_list[k])
		{
			cleanup_string_list(line_list, k);
			return (NULL);
		}
		ft_strlcpy(*(line_list + k), line, element_length + 1);
		line += element_length;
		k++;
	}
	line_list[k] = NULL;
	return (line_list);
}
