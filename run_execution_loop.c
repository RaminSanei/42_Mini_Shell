/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execution_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 17:31:10 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/////////////////////////////////////////////////////////child_process.c

int	get_command_count(t_mini *obj)
{
	int			num_commands;
	t_list_c	*cmd_node;

	if (obj == NULL || obj->cmd == NULL)
		return (0);
	num_commands = 0;
	cmd_node = obj->cmd;
	while (cmd_node)
	{
		num_commands++;
		cmd_node = cmd_node->next;
	}
	return (num_commands);
}

/////////////////////////////////////////////////////////

void	handle_child_process(t_mini *obj, t_list_c *curr_cmd, int *fd_pipe,
		char **env)
{
	free(obj->process_id);
	execute_child_task(obj, curr_cmd, fd_pipe, env);
	exit(EXIT_FAILURE);
}

void	handle_parent_process(t_mini *obj, t_list_c **curr_cmd, int *fd_pipe,
		int *pid_counter)
{
	execute_parent_process(obj, *curr_cmd, fd_pipe);
	*curr_cmd = (*curr_cmd)->next;
	(*pid_counter)++;
}

void	run_execution_loop(t_mini *obj, int main_fd_in, int main_fd_out,
		char **env)
{
	t_list_c	*curr_cmd;
	int			pid_counter;
	int			fd_pipe[2];

	curr_cmd = obj->cmd;
	pid_counter = 0;
	obj->process_id = safe_malloc(sizeof(int) * get_command_count(obj));
	while (curr_cmd)
	{
		if (pipe(fd_pipe) == -1)
			handle_error_void(obj, -1, "pipe error");
		obj->process_id[pid_counter] = fork();
		if (obj->process_id[pid_counter] == -1)
			handle_error_int(obj, -1, "fork error");
		else if (obj->process_id[pid_counter] == 0)
		{
			safely_close_file_descriptors(main_fd_in, main_fd_out);
			handle_child_process(obj, curr_cmd, fd_pipe, env);
		}
		else
			handle_parent_process(obj, &curr_cmd, fd_pipe, &pid_counter);
	}
}
