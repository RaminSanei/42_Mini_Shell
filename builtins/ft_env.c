/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:26 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 11:07:54 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list(t_list_e *inf)
{
	while (inf)
	{
		printf("%s\n", inf->content);
		inf = inf->f_ward;
	}
}

int	built_env(t_mini *shell, char *argv[])
{
	print_env_list(shell->inf);
	(void)argv;
	return (EXIT_SUCCESS);
}
