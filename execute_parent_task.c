/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_task.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 10:41:25 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe_read(t_mini *shell, int pipe_fds[2])
{
	handle_error_void(shell, dup2(pipe_fds[0], STDIN_FILENO), "dup2 error");
	safely_close_file_descriptors(pipe_fds[1], pipe_fds[0]);
}

void	execute_parent_task(t_mini *shell, t_list_c *current_act,
		int pipe_fds[2])
{
	if (current_act->f_ward == NULL)
	{
		close(STDIN_FILENO);
		return ;
	}
	setup_pipe_read(shell, pipe_fds);
}
