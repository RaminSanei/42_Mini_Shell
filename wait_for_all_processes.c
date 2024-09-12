/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_all_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 17:13:54 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	wait_for_child_process(t_mini *data, int process_index,
		int *exit_status)
{
	waitpid(data->process_id[process_index], exit_status, 0);
	set_and_return_exit_code(data, *exit_status);
}

void	release_memory(t_mini *data)
{
	if (data->process_id)
		free(data->process_id);
}

void	wait_for_all_processes(t_mini *data, int *exit_status)
{
	int	num_processes;
	int	i;

	num_processes = get_command_count(data);
	i = 0;
	while (i < num_processes)
	{
		wait_for_child_process(data, i, exit_status);
		i++;
	}
	release_memory(data);
}
