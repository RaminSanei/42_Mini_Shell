/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 17:58:12 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_toks_list(t_list **action_list)
{
	t_list	*next_node;
	t_list	*current_node;

	if (!action_list || !*action_list)
		return ;
	current_node = *action_list;
	while (current_node)
	{
		next_node = current_node->f_ward;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*action_list = NULL;
}

void	process_expansion_and_actions(t_mini *shell)
{
	perform_expansion(shell);
	shell->c_list = build_action_list(shell->elem);
	free_toks_list(&(shell->elem));
}

int	actionize_and_validate_syntax(t_mini *shell)
{
	shell->elem = generate_actions(&(shell->line));
	if (validate_syntax(shell->elem) == EXIT_FAILURE)
	{
		free_toks_list(&(shell->elem));
		return (set_and_return_drop_num(shell, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	validate_quotes(t_mini *shell)
{
	if (check_unclosed_quotes(shell->line) == true)
		return (set_and_return_drop_num(shell, 130));
	return (EXIT_SUCCESS);
}

void	parse_input(t_mini *shell)
{
	if (validate_quotes(shell) == 130)
	{
		shell->drop_num = 130;
		return ;
	}
	if (actionize_and_validate_syntax(shell) == EXIT_FAILURE)
	{
		shell->drop_num = EXIT_FAILURE;
		return ;
	}
	process_expansion_and_actions(shell);
	set_and_return_drop_num(shell, EXIT_SUCCESS);
}
