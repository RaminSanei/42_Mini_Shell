/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:19 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:08:27 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_inf_string(char *prefix, char *value)
{
	char	*result;
	char	*temp;

	result = ft_strdup(prefix);
	temp = ft_strnjoin(result, value, 1);
	return (temp);
}

void	set_environment_variables(t_mini *shell)
{
	char	*oldpwd_inf;
	char	*pwd_inf;

	pwd_inf = create_inf_string("PWD=", shell->work_dir);
	set_environment_variable(pwd_inf, &shell->inf);
	free(pwd_inf);
	oldpwd_inf = create_inf_string("OLDPWD=", shell->old_work_dir);
	set_environment_variable(oldpwd_inf, &shell->inf);
	free(oldpwd_inf);
}

int	change_directory_path(char *path)
{
	if (chdir(path) != 0)
		handle_cd_error(path);
	return (EXIT_SUCCESS);
}

int	update_directory(char **path, char *new_path)
{
	if (change_directory_path(new_path) == MINUS1)
		return (MINUS1);
	free(*path);
	*path = ft_strdup(new_path);
	return (EXIT_SUCCESS);
}

int	built_cd(t_mini *shell, char *argv[])
{
	if (argv[1] == NULL)
	{
		return (EXIT_SUCCESS);
	}
	else if (argv[2] != NULL)
	{
		return (handle_cd_error(argv[1]));
	}
	else
	{
		if (update_directory(&shell->work_dir, argv[1]) == MINUS1)
			return (handle_cd_error(argv[1]));
		built_cd_erase_doub(shell, argv);
	}
	set_environment_variables(shell);
	return (EXIT_SUCCESS);
}
