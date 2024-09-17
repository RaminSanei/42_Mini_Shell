/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell_inf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:28 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:20:41 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell_inf_helper(char **inf, t_mini *shell)
{
	while (*inf)
	{
		add_inf_variable(&shell->inf, *inf);
		inf++;
	}
}

void	initialize_shell_inf(t_mini *shell, char **inf)
{
	char	*work_dir;

	work_dir = getcwd(NULL, 0);
	shell->inf = NULL;
	shell->drop_num = 0;
	shell->old_work_dir = ft_strdup(work_dir);
	shell->work_dir = ft_strdup(work_dir);
	initialize_shell_inf_helper(inf, shell);
	shell->c_list = NULL;
	shell->elem = NULL;
}
