/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/08 18:06:28 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command_index(const char *command_name, t_biltin_c commands[],
		int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		if (strcmp(commands[i].name, command_name) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

bool	is_builtin_command(char **argv)
{
	t_biltin_c	commands[NUM_B_CMD];
	int			command_index;

	commands = init_biltin_cmd();
	command_index = find_command_index(argv[0], commands, NUM_B_CMD);
	if (command_index != -1)
		return (true);
	printf("Command not found: %s\n", argv[0]);
	return (false);
}

// t_biltin_c	init_biltin_cmd(void)
// {
// 	t_biltin_c	commands[NUM_B_CMD];
// 	commands[0].name = "cd";
    
// 	return (commands);
// }
