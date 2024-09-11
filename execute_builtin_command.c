/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 19:27:21 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **argv, t_mini *obj, t_builtin_c *builtins)
{
	int	i;

	i = 0;
	while (i < NUM_B_CMD)
	{
		if (strcmp(builtins[i].name, argv[0]) == 0)
		{
			return (builtins[i].function(argv, obj));
		}
		i++;
	}
	return (MINUS1);
}

int	execute_builtin_command(t_mini *obj, char *argv[])
{
	t_builtin_c	builtins[NUM_B_CMD];

	init_builtin_cmd(builtins);
	if (argv[0] == NULL)
	{
		return (EXIT_SUCCESS);
	}
	if (execute_builtin(argv, obj, builtins) == MINUS1)
	{
		printf(CMD_N_F " %s\n", argv[0]);
		return (MINUS1);
	}
	return (EXIT_SUCCESS);
}
