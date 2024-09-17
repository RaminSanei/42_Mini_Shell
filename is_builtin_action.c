/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 10:35:49 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin_act(t_builtin_c actions[])
{
	actions[0].name = "cd";
	actions[0].function = built_cd;
	actions[1].name = "echo";
	actions[1].function = built_echo;
	actions[2].name = "export";
	actions[2].function = built_export;
	actions[3].name = "unset";
	actions[3].function = built_unset;
	actions[4].name = "pwd";
	actions[4].function = built_pwd;
	actions[5].name = "env";
	actions[5].function = built_env;
	actions[6].name = "exit";
	actions[6].function = built_exit;
}

int	find_action_index(const char *action_name, t_builtin_c actions[],
		int num_actions)
{
	int	k;

	k = 0;
	while (k < num_actions)
	{
		if (strcmp(actions[k].name, action_name) == 0)
			return (k);
		k++;
	}
	return (MINUS1);
}

bool	is_builtin_action(char **argv)
{
	t_builtin_c	actions[NUM_B_CMD];
	int			action_index;

	init_builtin_act(actions);
	action_index = find_action_index(argv[0], actions, NUM_B_CMD);
	if (action_index != MINUS1)
	{
		return (true);
	}
	return (false);
}
