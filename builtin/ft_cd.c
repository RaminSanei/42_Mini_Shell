/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:19 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 13:41:55 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//////handle-cd-error//////
int	handle_cd_error(char *path)
{
	printf(ERROR_DIR "%s\n", path);
	return (MINUS1);
}
//////handle-cd-error//////

//////update_enviroment//////
static char	*create_env_string(const char *prefix, const char *value)
{
	char	*result;
	char	*temp;

	result = ft_strdup(prefix);
	temp = ft_strnjoin(result, value, 1);
	free(result);
	return (temp);
}

void	set_environment_variables(t_mini *obj)
{
	char	*pwd_env;
	char	*oldpwd_env;

	pwd_env = create_env_string("PWD=", obj->pwd);
	oldpwd_env = create_env_string("OLDPWD=", obj->oldpwd);
	set_environment_variable(pwd_env, &obj->env);
	set_environment_variable(oldpwd_env, &obj->env);
	free(pwd_env);
	free(oldpwd_env);
}
//////update_enviroment//////

/////change-directory/////

void	free_and_dup(char **dest, char *src)
{
	free(*dest);
	*dest = ft_strdup(src);
}

void	exchange_strings(char **s1, char **s2)
{
	char	*tmp;

	tmp = ft_strdup(*s1);
	free_and_dup(s1, *s2);
	free_and_dup(s2, tmp);
	free(tmp);
}

/////change-directory/////

int	change_directory(char *path)
{
	if (chdir(path) != 0)
		handle_cd_error(path);
	return (EXIT_SUCCESS);
}

//////cd-func//////

int	update_directory(char **path, char *new_path)
{
	if (change_directory(new_path) == MINUS1)
		return (MINUS1);
	free(*path);
	*path = ft_strdup(new_path);
	return (EXIT_SUCCESS);
}

int	cd_to_previous_directory(t_mini *obj)
{
	if (change_directory(obj->oldpwd) == MINUS1)
		return (MINUS1);
	exchange_strings(&obj->oldpwd, &obj->pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_mini *obj, char *argv[])
{
	if (argv[1] == NULL)
		return (EXIT_SUCCESS);
	else if (argv[2] != NULL)
		return (handle_cd_error(argv[1]));
	if (ft_strcmp(argv[1], "-") == 0)
	{
		if (cd_to_previous_directory(obj) == MINUS1)
			return (MINUS1);
	}
	else
	{
		if (update_directory(&obj->pwd, argv[1]) == MINUS1)
			return (handle_cd_error(argv[1]));
		free(obj->oldpwd);
		obj->oldpwd = ft_strdup(obj->pwd);
	}
	set_environment_variables(obj);
	return (EXIT_SUCCESS);
}
