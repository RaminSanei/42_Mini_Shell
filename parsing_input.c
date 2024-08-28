/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/28 19:36:04 by ssanei           ###   ########.fr       */
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

char	*extract_token(char **input, int index)
{
	char	*token;
	char	quote_char;

	quote_char = 0;
	token = (char *)safe_malloc(allocate_memory_for_token(*input) + 1);
	while (**input)
	{
		if (**input == 34 || **input == 39)
		{
			if (**input == quote_char)
				quote_char = 0;
			else if (quote_char == 0)
				quote_char = **input;
		}
		token[index++] = **input;
		if (**input == 0 || is_separator(input, quote_char))
			break ;
		(*input)++;
	}
	token[index] = 0;
	return (token);
}

void	assign_token_type(t_list **token_list)
{
	t_list	*current_token;

	if (!token_list || !*token_list)
		return ;
	current_token = *token_list;
	while (current_token->next)
		current_token = current_token->next;
	if (are_strings_equal(current_token->content, ""))
		current_token->t_type = EMPTY;
	else if (are_strings_equal(current_token->content, ">"))
		current_token->t_type = TRUNC;
	else if (are_strings_equal(current_token->content, "|"))
		current_token->t_type = PIPE;
	else if (are_strings_equal(current_token->content, "<"))
		current_token->t_type = INPUT;
	else if (are_strings_equal(current_token->content, "<<"))
		current_token->t_type = HEREDOC;
	else if (are_strings_equal(current_token->content, ">>"))
		current_token->t_type = APPEND;
	else if (!current_token->prev || current_token->prev->t_type == PIPE
		|| (current_token->prev->prev
			&& current_token->prev->prev->t_type == HEREDOC))
		current_token->t_type = COMMAND;
	else
		current_token->t_type = ARG;
}

void	add_token_to_list(t_list **token_list, char *current_token)
{
	t_list	*new_token;
	t_list	*current;

	new_token = (t_list *)safe_malloc(sizeof(t_list));
	new_token->content = ft_strdup(current_token);
	new_token->t_type = NULL;
	new_token->prev = NULL;
	new_token->next = NULL;
	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	current = *token_list;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	add_token_to_list(t_list **token_list, const char *current_token)
{
	t_list	*new_token;
	t_list	*current;

	new_token = (t_list *)safe_malloc(sizeof(t_list));
	new_token->content = ft_strdup(current_token);
	if (!new_token->content)
	{
		free(new_token);
		return ;
	}
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}

void	generate_tokens_helper(char **input, t_list *token_list,
		char *current_token)
{
	int	index;

	index = 0;
	while (**input)
	{
		skip_whitespace(input);
		if (**input == 0)
			break ;
		current_token = extract_token(input, index);
		add_token_to_list(&token_list, current_token);
		determine_token_type(&token_list);
		free(current_token);
		if (**input == 0)
			break ;
		(*input)++;
		skip_whitespace(input);
	}
}

t_list	*generate_tokens(char **input)
{
	t_list	*token_list;
	char	*current_token;

	current_token = NULL;
	token_list = NULL;
	generate_tokens_helper(input, token_list, current_token);
	return (token_list);
}

int	parsing_input(t_mini *shell)
{
	if (check_unclosed_quotes(shell->line) == EXIT_FAILURE)
		return (set_and_return_exit_code(shell, EXIT_FAILURE));
	shell->toks = generate_tokens(&shell->line);
}
