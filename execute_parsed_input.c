/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parsed_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/07 10:44:39 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
///// 1. handle_error_int for dup and fork
int	handle_error_int(t_mini *shell, int result, const char *error_msg)
{
	if (result == -1)
	{
		ft_putstr_fd("minishell error: ", STDERR_FILENO);
		perror(error_msg);
		exit(set_and_return_exit_code(shell, 130));
	}
	return (result);
}
///// 2. handle_error_void for dup2 and pipe
void	handle_error_void(t_mini *shell, int result, const char *error_msg)
{
	if (result == -1)
	{
		ft_putstr_fd("minishell error: ", STDERR_FILENO);
		perror(error_msg);
		exit(determine_exit_code(shell, 130));
	}
}
///// 3. close_fds for closing file descriptors
void	safely_close_file_descriptors(int descriptor1, int descriptor2)
{
	if (descriptor1 != -1)
		close(descriptor1);
	if (descriptor2 != -1)
		close(descriptor2);
}


int	save_fds(int *saved_stdin, int *saved_stdout, t_mini *shell)
{
	// *saved_stdin = duplicate1_fd_error(shell, dup(STDIN_FILENO));
	*saved_stdin = handle_error_int(shell, dup(STDIN_FILENO), "dup error");
	// *saved_stdout = duplicate1_fd_error(shell, dup(STDOUT_FILENO));
	*saved_stdout = handle_error_int(shell, dup(STDOUT_FILENO), "dup error");
	if (*saved_stdin == -1 || *saved_stdout == -1)
		return (130);
	return (EXIT_SUCCESS);
}

void	restore_fds(t_mini *shell, int saved_stdin, int saved_stdout)
{
	// duplicate_fd_error(shell, dup2(saved_stdin, STDIN_FILENO));
	handle_error_void(shell, dup2(saved_stdin, STDIN_FILENO), "dup2 error");
	// duplicate_fd_error(shell, dup2(saved_stdout, STDOUT_FILENO));
	handle_error_void(shell, dup2(saved_stdout, STDOUT_FILENO), "dup2 error");
	// close_fds(saved_stdin, saved_stdout);
	safely_close_file_descriptors(saved_stdin, saved_stdout);
}

// int	execute_builtin_commands(t_mini *shell, t_list_c *current_command)
// {
// 	if (apply_redirections(current_command) == 130)
// 		return (set_and_return_exit_code(shell, 130), 130);
// 	run_builtin(shell, current_command->content);
// 	return (EXIT_SUCCESS);
// }

int	run_command_execution(t_mini *shell, char **env)
{
	int	exit_status;
	int	saved_stdin;
	int	saved_stdout;

	if (save_fds(&saved_stdin, &saved_stdout, shell) == 130)
		return (130);
	handle_heredoc(shell);
	// if (shell->cmd && shell->cmd->content[0]
	// 	&& is_builtin_command(shell->cmd->content) && shell->cmd->next == NULL)
	// {
	// 	if (execute_builtin_commands(shell, shell->cmd) == 130)
	// 		return (130);
	// }
	// else if (shell->cmd && shell->cmd->content[0])
	// {
	// 	run_execution_loop(shell, saved_stdin, saved_stdout, env);
	// 	wait_for_all_processes(shell, &exit_status);
	// }
	restore_fds(shell, saved_stdin, saved_stdout);
	return (130);
}
