/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parsed_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 18:03:01 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safely_close_file_descriptors(int descriptor1, int descriptor2)
{
	if (descriptor1 != -1)
		close(descriptor1);
	if (descriptor2 != -1)
		close(descriptor2);
}

int	save_fds(int *saved_stdin, int *saved_stdout, t_mini *shell)
{
	*saved_stdin = handle_error_int(shell, dup(STDIN_FILENO), "dup error");
	*saved_stdout = handle_error_int(shell, dup(STDOUT_FILENO), "dup error");
	if (*saved_stdin == -1 || *saved_stdout == -1)
		return (130);
	return (EXIT_SUCCESS);
}

void	restore_fds(t_mini *shell, int saved_stdin, int saved_stdout)
{
	handle_error_void(shell, dup2(saved_stdin, STDIN_FILENO), "dup2 error");
	handle_error_void(shell, dup2(saved_stdout, STDOUT_FILENO), "dup2 error");
	safely_close_file_descriptors(saved_stdin, saved_stdout);
}

int	execute_builtin_actions(t_mini *shell, t_list_c *current_action)
{
	int	exit_status;

	if (configure_streams(current_action) == EXIT_FAILURE)
	{
		exit_status = set_and_return_drop_num(shell, 130);
		return (exit_status);
	}
	execute_builtin_action(shell, current_action->content);
	return (EXIT_SUCCESS);
}

void	run_action_execution(t_mini *shell, char **inf)
{
	int	saved_stdin;
	int	exit_status;
	int	saved_stdout;

	if (save_fds(&saved_stdin, &saved_stdout, shell) == 130)
		shell->drop_num = 130;
	handle_heredoc(shell);
	if (shell->c_list && shell->c_list->content[0]
		&& is_builtin_action(shell->c_list->content)
		&& shell->c_list->f_ward == NULL)
	{
		if (execute_builtin_actions(shell, shell->c_list) == 130)
			shell->drop_num = 130;
	}
	else if (shell->c_list && shell->c_list->content[0])
	{
		run_execution_loop(shell, saved_stdin, saved_stdout, inf);
		wait_for_all_processes(shell, &exit_status);
	}
	restore_fds(shell, saved_stdin, saved_stdout);
	shell->drop_num = 130;
}
