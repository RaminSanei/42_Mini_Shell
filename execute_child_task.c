/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_task.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 17:30:19 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	manage_piping(t_mini *data, t_list_c *current_cmd, int pipe_fds[2])
{
	if (current_cmd->next != NULL)
	{
		handle_error_void(data, dup2(pipe_fds[1], STDOUT_FILENO), "dup2 error");
		safely_close_file_descriptors(pipe_fds[0], pipe_fds[1]);
	}
}

void	setup_redirections_and_exit_on_failure(t_mini *data,
		t_list_c *current_cmd)
{
	if (apply_redirections(current_cmd) == 130)
	{
		exit(set_and_return_exit_code(data, 130));
	}
}

void	execute_command_or_builtin(t_mini *data, t_list_c *current_cmd,
		char *exec_path, char **env)
{
	if (current_cmd->content[0] && is_builtin_command(current_cmd->content))
		execute_builtin_command(data, current_cmd->content);
	else
		child_process_execute(data, current_cmd, env);
}

void	execute_child_task(t_mini *data, t_list_c *current_cmd, int pipe_fds[2],
		char **env)
{
	char	*exec_path;

	exec_path = NULL;
	manage_piping(data, current_cmd, pipe_fds);
	setup_redirections_and_exit_on_failure(data, current_cmd);
	execute_command_or_builtin(data, current_cmd, exec_path, env);
	exit(set_and_return_exit_code(data, 130));
}
