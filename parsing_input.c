/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 10:57:25 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(const char *line)
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
				return (EXIT_FAILURE);
			}
		}
		line++;
	}
	return (EXIT_SUCCESS);
}

char	*extract_token(char **input, int index)
{
	char	*action;
	char	quote_char;

	quote_char = 0;
	action = (char *)safe_malloc(allocate_memory_for_token(*input) + 1);
	while (**input)
	{
		if (**input == 34 || **input == 39)
		{
			if (**input == quote_char)
				quote_char = 0;
			else if (quote_char == 0)
				quote_char = **input;
		}
		action[index++] = **input;
		if (**input == 0 || is_separator(input, quote_char))
			break ;
		(*input)++;
	}
	action[index] = 0;
	return (action);
}

void	assign_token_type(t_list **token_list)
{
	t_list	*current_token;

	if (!token_list || !*token_list)
		return ;
	current_token = *token_list;
	while (current_token->f_ward)
		current_token = current_token->f_ward;
	if (are_strings_equal(current_token->content, ""))
		current_token->kind = EMPTY;
	else if (are_strings_equal(current_token->content, ">"))
		current_token->kind = TRUNC;
	else if (are_strings_equal(current_token->content, "|"))
		current_token->kind = PIPE;
	else if (are_strings_equal(current_token->content, "<"))
		current_token->kind = INPUT;
	else if (are_strings_equal(current_token->content, "<<"))
		current_token->kind = HEREDOC;
	else if (are_strings_equal(current_token->content, ">>"))
		current_token->kind = APPEND;
	else if (!current_token->b_ward || current_token->b_ward->kind == PIPE
		|| (current_token->b_ward->b_ward
			&& current_token->b_ward->b_ward->kind == HEREDOC))
		current_token->kind = CMD;
	else
		current_token->kind = ARG;
}

void	add_token_to_list(t_list **token_list, char *current_token)
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
	new_token->f_ward = NULL;
	new_token->b_ward = NULL;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->f_ward)
			current = current->f_ward;
		current->f_ward = new_token;
		new_token->b_ward = current;
	}
}

// void	generate_tokens_helper(char **input, t_list *token_list,
// 		char *current_token)
// {
// 	int	index;

// 	index = 0;
// 	while (**input)
// 	{
// 		printf("hello6\n");
// 		printf("input: %s\n", *input);
// 		skip_whitespace(input);
// 		if (*(*input) == '\0')
// 		{
// 			printf("hello7\n\n");
// 			break ;
// 		}

// 		current_token = extract_token(input, index);
// 		printf("hello8\n");
// 		printf("current_token: %s\n", current_token);

// 		add_token_to_list(&token_list, current_token);
// 		printf("hello9\n");
// 		assign_token_type(&token_list);
// 		printf("action: %s\n", token_list->content);
// 		free(current_token);
// 		printf("hello20\n");
// 		printf("input:\n %c\n", **input);
// 		if (*(*input) == '\0')
// 		{
// 			printf("hello10\n");
// 			break ;
// 		}
// 		(*input)++;
// 		skip_whitespace(input);
// 	}
// 	printf("hello11");
// }

t_list	*generate_tokens(char **input)
{
	t_list	*token_list;
	char	*current_token;
	int		index;

	index = 0;
	current_token = NULL;
	token_list = NULL;
	while (**input)
	{
		skip_whitespace(input);
		if (*(*input) == '\0')
		{
			break ;
		}
		current_token = extract_token(input, index);
		add_token_to_list(&token_list, current_token);
		assign_token_type(&token_list);
		free(current_token);
		if (*(*input) == '\0')
		{
			break ;
		}
		(*input)++;
		skip_whitespace(input);
	}
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
		next_node = current_node->f_ward;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*token_list = NULL;
}
void	process_expansion_and_actions(t_mini *shell)
{
	perform_expansion(shell);
	shell->c_list = build_action_list(shell->elem);
	free_toks_list(&(shell->elem));
}

int	tokenize_and_validate_syntax(t_mini *shell)
{
	shell->elem = generate_tokens(&(shell->line));
	if (validate_syntax(shell->elem) == EXIT_FAILURE)
	{
		free_toks_list(&(shell->elem));
		return (set_and_return_drop_num(shell, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	validate_quotes(t_mini *shell)
{
	if (check_unclosed_quotes(shell->line) == EXIT_FAILURE)
		return (set_and_return_drop_num(shell, 130));
	return (EXIT_SUCCESS);
}

int	parse_input(t_mini *shell)
{
	if (validate_quotes(shell) == 130)
		return (shell->drop_num);
	if (tokenize_and_validate_syntax(shell) == EXIT_FAILURE)
		return (shell->drop_num);
	process_expansion_and_actions(shell);
	return (set_and_return_drop_num(shell, EXIT_SUCCESS));
}
