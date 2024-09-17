/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execution_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:19:29 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_action_count(t_mini *shell)
{
	int			num_actions;
	t_list_c	*act_node;

	if (shell == NULL || shell->c_list == NULL)
		return (0);
	num_actions = 0;
	act_node = shell->c_list;
	while (act_node)
	{
		num_actions++;
		act_node = act_node->f_ward;
	}
	return (num_actions);
}

void	handle_child_process(t_mini *shell, t_list_c *curr_act, int *fd_pipe,
		char **inf)
{
	free(shell->process_num);
	execute_child_task(shell, curr_act, fd_pipe, inf);
	exit(EXIT_FAILURE);
}

void	handle_parent_process(t_mini *shell, t_list_c **curr_act, int *fd_pipe,
		int *pid_counter)
{
	execute_parent_task(shell, *curr_act, fd_pipe);
	*curr_act = (*curr_act)->f_ward;
	(*pid_counter)++;
}

void	run_execution_loop(t_mini *shell, int main_fd_in, int main_fd_out,
		char **inf)
{
	t_list_c	*curr_act;
	int			pid_counter;
	int			fd_pipe[2];

	curr_act = shell->c_list;
	pid_counter = 0;
	shell->process_num = safe_malloc(sizeof(int) * get_action_count(shell));
	while (curr_act)
	{
		if (pipe(fd_pipe) == -1)
			handle_error_void(shell, -1, "pipe error");
		shell->process_num[pid_counter] = fork();
		if (shell->process_num[pid_counter] == -1)
			handle_error_int(shell, -1, "fork error");
		else if (shell->process_num[pid_counter] == 0)
		{
			safely_close_file_descriptors(main_fd_in, main_fd_out);
			handle_child_process(shell, curr_act, fd_pipe, inf);
		}
		else
			handle_parent_process(shell, &curr_act, fd_pipe, &pid_counter);
	}
}
