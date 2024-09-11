/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_by_delimiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 15:33:04 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_words(const char *str, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == delimiter)
			in_word = 0;
		str++;
	}
	return (count);
}

int	word_length(const char *str, char delimiter)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != delimiter)
		len++;
	return (len);
}

char	*copy_word(const char *str, int len)
{
	char	*word;

	word = safe_malloc(len + 1);
	ft_strlcpy(word, str, len + 1);
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

char	**split_string_by_delimiter(const char *str, char delimiter)
{
	int		i;
	int		word_len;
	int		word_count;
	char	**array;

	word_count = count_words(str, delimiter);
	array = safe_malloc((word_count + 1) * sizeof(char *));
	i = 0;
	while (i < word_count)
	{
		while (*str && *str == delimiter)
			str++;
		word_len = word_length(str, delimiter);
		array[i] = copy_word(str, word_len);
		if (!array[i])
			return (free_word_array(array, i));
		str += word_len;
		i++;
	}
	array[word_count] = NULL;
	return (array);
}
