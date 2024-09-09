/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:02:50 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 12:24:07 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int flag)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (flag == 4)
		result = ft_strdup(s2);
	else
		result = ft_strjoin(s1, s2);
	if (flag != 3 && s1)
		free(s1);
	if (flag > 1 && s2)
		free(s2);
	return (result);
}

char	*handle_special_cases(const char *key, int exit_num)
{
	if (*key == '\0')
		return (ft_strdup("$"));
	else if (*key == '$')
		return (ft_itoa(getpid()));
	else if (*key == '?')
		return (ft_itoa(exit_num));
	return (NULL);
}

char	*lookup_env_variable(t_list_e *env_list, const char *key)
{
	char	*value;
	int		key_length;
	int		key_equal_length;

	value = NULL;
	key_length = ft_strlen(key);
	while (env_list)
	{
		key_equal_length = find_key_length(env_list->content);
		if (ft_strncmp(key, env_list->content, key_length) == 0
			&& ft_strncmp(env_list->content, key, key_equal_length) == 0)
		{
			value = ft_strdup(ft_strchr(env_list->content, '=') + 1);
			break ;
		}
		env_list = env_list->next;
	}
	return (value);
}

char	*retrieve_env_value(t_mini *shell, const char *key)
{
	char	*result;

	result = handle_special_cases(key, shell->exit_num);
	if (result != NULL)
		return (result);
	result = lookup_env_variable(shell->env, key);
	if (result != NULL)
		return (result);
	return (ft_strdup(""));
}

char	*expand_token(t_mini *shell, char *token)
{
	if (ft_strchr(token, '$'))
		return (ft_strnjoin(NULL, retrieve_env_value(shell, token + 1), 2));
	return (ft_strdup(token));
}

char	*non_qts(t_mini *shell, char **tokens, int *index)
{
	char	*result;
	char	*expanded_token;
	char	*temp;

	result = NULL;
	while (ft_strcmp(tokens[*index], "\"") && ft_strcmp(tokens[*index], "\'")
			&& tokens[*index])
	{
		expanded_token = expand_token(shell, tokens[*index]);
		if (result)
		{
			temp = result;
			result = ft_strjoin(temp, expanded_token);
			free(temp);
		}
		else
		{
			result = expanded_token;
		}
		(*index)++;
	}
	return (result);
}

char	double_qts(t_mini *shell, char **tokens, int *index)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(tokens[*index], "\"") && tokens[*index])
		(*index)++;
	while (ft_strcmp(tokens[*index], "\"") && tokens[*index])
	{
		if (ft_strchr(tokens[*index], '$'))
			result = ft_strnjoin(result, retrieve_env_value(shell,
						tokens[*index] + 1), 2);
		else
			result = ft_strnjoin(result, tokens[*index], 1);
		(*index)++;
	}
	if (!ft_strcmp(tokens[*index], "\"") && tokens[*index])
		(*index)++;
	return (result);
}

char	*single_qts(char **tokens, int *index)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(tokens[*index], "\'") && tokens[*index])
		(*index)++;
	while (ft_strcmp(tokens[*index], "\'") && tokens[*index])
	{
		result = ft_strnjoin(result, tokens[*index], 1);
		(*index)++;
	}
	if (!ft_strcmp(tokens[*index], "\'") && tokens[*index])
		(*index)++;
	return (result);
}

void	expand_word(t_mini *shell, t_list *toks, char **arguments, int *index)
{
	if (!ft_strcmp(arguments[*index], "\'"))
		toks->content = ft_strnjoin(toks->content, single_qts(arguments, index),
				2);
	else if (!ft_strcmp(arguments[*index], "\""))
		toks->content = ft_strnjoin(toks->content, double_qts(shell, arguments,
					index), 2);
	else
		toks->content = ft_strnjoin(toks->content, non_qts(shell, arguments,
					index), 2);
}

void	process_token(t_mini *shell, t_list *toks)
{
	char	**split_tokens;
	int		index;

	split_tokens = ft_split(toks->content, ' ');
	free(toks->content);
	toks->content = NULL;
	index = 0;
	while (split_tokens[index])
	{
		expand_word(shell, toks, split_tokens, &index);
	}
	free_word_array(split_tokens);
}

void	perform_expansion(t_mini *shell)
{
	t_list *current_token;

	current_token = shell->toks;
	while (current_token)
	{
		process_token(shell, current_token);
		current_token = current_token->next;
	}
}
