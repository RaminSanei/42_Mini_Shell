/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_by_delimiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 17:23:53 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_numbers(const char *line, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line)
	{
		if (*line != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*line == delimiter)
			in_word = 0;
		line++;
	}
	return (count);
}

int	word_length(const char *line, char delimiter)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != delimiter)
		len++;
	return (len);
}

char	*copy_word(const char *line, int len)
{
	char	*word;

	word = safe_malloc(len + 1);
	ft_strlcpy(word, line, len + 1);
	return (word);
}

char	**free_word_array(char **array, int words_allocated)
{
	while (words_allocated > 0)
	{
		free(array[words_allocated]);
		words_allocated--;
	}
	free(array);
	return (NULL);
}

char	**split_string_by_delimiter(const char *line, char delimiter)
{
	int		k;
	int		word_len;
	int		word_count;
	char	**array;

	word_count = word_numbers(line, delimiter);
	array = safe_malloc((word_count + 1) * sizeof(char *));
	k = 0;
	while (k < word_count)
	{
		while (*line && *line == delimiter)
			line++;
		word_len = word_length(line, delimiter);
		array[k] = copy_word(line, word_len);
		if (!array[k])
			return (free_word_array(array, k));
		line += word_len;
		k++;
	}
	array[word_count] = NULL;
	return (array);
}
