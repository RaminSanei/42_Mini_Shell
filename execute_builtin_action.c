/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_action.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 10:53:42 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **argv, t_mini *shell, t_builtin_c *builtins)
{
	int	k;

	k = 0;
	while (k < NUM_B_CMD)
	{
		if (strcmp(builtins[k].name, argv[0]) == 0)
			return (builtins[k].function(shell, argv));
		k++;
	}
	return (MINUS1);
}

int	execute_builtin_action(t_mini *shell, char *argv[])
{
	t_builtin_c	builtins[NUM_B_CMD];

	init_builtin_act(builtins);
	if (argv[0] == NULL)
		return (EXIT_SUCCESS);
	if (execute_builtin(argv, shell, builtins) == MINUS1)
	{
		printf(CMD_N_F " %s\n", argv[0]);
		return (MINUS1);
	}
	return (EXIT_SUCCESS);
}
