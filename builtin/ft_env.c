/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:26 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 13:44:11 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_env_list(t_list_e *env)
{
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

int	ft_env(t_mini *obj, char *argv[])
{
	(void)argv;
	print_env_list(obj->env);
	return (EXIT_SUCCESS);
}
