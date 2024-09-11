/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 19:28:01 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin_cmd(t_builtin_c b_commands[])
{
	b_commands[0].name = "cd";
	b_commands[0].function = ft_cd;
	b_commands[1].name = "echo";
	b_commands[1].function = ft_echo;
	b_commands[2].name = "export";
	b_commands[2].function = ft_export;
	b_commands[3].name = "unset";
	b_commands[3].function = ft_unset;
	b_commands[4].name = "pwd";
	b_commands[4].function = ft_pwd;
	b_commands[5].name = "env";
	b_commands[5].function = ft_env;
	b_commands[6].name = "exit";
	b_commands[6].function = ft_exit;
}

int	find_command_index(const char *command_name, t_builtin_c commands[],
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
	t_builtin_c	commands[NUM_B_CMD];
	int			command_index;

	init_builtin_cmd(commands);
	command_index = find_command_index(argv[0], commands, NUM_B_CMD);
	if (command_index != -1)
		return (true);
	printf(CMD_N_F " %s\n", argv[0]);
	return (false);
}
