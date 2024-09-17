/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_task.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 11:15:19 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_piping(t_mini *shell, t_list_c *current_act, int pipe_fds[2])
{
	if (current_act->f_ward != NULL)
	{
		handle_error_void(shell, dup2(pipe_fds[1], STDOUT_FILENO),
			"dup2 error");
		safely_close_file_descriptors(pipe_fds[0], pipe_fds[1]);
	}
}

void	setup_streams_and_exit_on_failure(t_mini *shell,
		t_list_c *current_act)
{
	if (configure_streams(current_act) == 130)
	{
		exit(set_and_return_drop_num(shell, 130));
	}
}

void	execute_action_or_builtin(t_mini *shell, t_list_c *current_act,
		char **inf)
{
	if (current_act->content[0] && is_builtin_action(current_act->content))
		execute_builtin_action(shell, current_act->content);
	else
		handle_child_operation(shell, current_act, inf);
}

void	execute_child_task(t_mini *shell, t_list_c *current_act,
		int pipe_fds[2], char **inf)
{
	char	*exec_path;

	exec_path = NULL;
	manage_piping(shell, current_act, pipe_fds);
	setup_streams_and_exit_on_failure(shell, current_act);
	execute_action_or_builtin(shell, current_act, inf);
	exit(set_and_return_drop_num(shell, 130));
}
