/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/31 14:14:51 by ssanei           ###   ########.fr       */
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
		current_token->t_type = CMD;
	else
		current_token->t_type = ARG;
}

// void	add_token_to_list(t_list **token_list, char *current_token)
// {
// 	t_list	*new_token;
// 	t_list	*current;

// 	new_token = (t_list *)safe_malloc(sizeof(t_list));
// 	new_token->content = ft_strdup(current_token);
// 	new_token->t_type = NULL;
// 	new_token->prev = NULL;
// 	new_token->next = NULL;
// 	if (!*token_list)
// 	{
// 		*token_list = new_token;
// 		return ;
// 	}
// 	current = *token_list;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_token;
// 	new_token->prev = current;
// }

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
		assign_token_type(&token_list);
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


void	free_toks_list(t_list **token_list)
{
	t_list	*next_node;
	t_list	*current_node;

	if (!token_list || !*token_list)
		return ;
	current_node = *token_list;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*token_list = NULL;
}
// void	process_expansion_and_commands(t_mini *shell)
// {
// 	perform_expansion(shell);
// 	shell->commands = build_command_list(shell->tokens);
// 	free_toks_list(&(shell->tokens));
// }

int	tokenize_and_validate_syntax(t_mini *shell)
{
	shell->toks = generate_tokens(&(shell->line));
	if (validate_syntax(shell->toks) == EXIT_FAILURE)
	{
		free_toks_list(&(shell->toks));
		return (set_exit_code(shell, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	validate_quotes(t_mini *shell)
{
	if (check_unclosed_quotes(shell->line) == EXIT_FAILURE)
		return (set_and_return_exit_code(shell, 130));
	return (EXIT_SUCCESS);
}

int	parse_input(t_mini *shell)
{
	if (validate_quotes(shell) == 130)
		return (shell->exit_num);
	if (tokenize_and_validate_syntax(shell) == EXIT_FAILURE)
		return (shell->exit_num);
	// process_expansion_and_commands(context);
	// return (set_exit_code(context, SUCCESS));
}
