/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 16:11:43 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	setup_pipe_read(t_mini *data, int pipe_fds[2])
{
	handle_error_void(data, dup2(pipe_fds[0], STDOUT_FILENO), "dup2 error");
	safely_close_file_descriptors(pipe_fds[1], pipe_fds[0]);
}

void	execute_parent_process(t_mini *data, t_list_c *current_cmd,
		int pipe_fds[2])
{
	if (current_cmd->next == NULL)
	{
		close(STDIN_FILENO);
		return ;
	}
	setup_pipe_read(data, pipe_fds);
}
