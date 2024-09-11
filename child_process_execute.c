/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 19:27:03 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*construct_full_path_helper(const char *path_element, const char *cmd,
		int path_len, int cmd_len)
{
	char	*full_path;

	full_path = safe_malloc(path_len + cmd_len + 2);
	ft_strlcpy(full_path, path_element, path_len + 1);
	ft_strlcpy(full_path + path_len, "/", 2);
	ft_strlcpy(full_path + path_len + 1, cmd, cmd_len + 1);
	return (full_path);
}

char	*construct_full_path(const char *path_element, const char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*full_path;

	if (!path_element || !cmd)
		return (NULL);
	path_len = ft_strlen(path_element);
	cmd_len = ft_strlen(cmd);
	full_path = construct_full_path_helper(path_element, cmd, path_len,
			cmd_len);
	return (full_path);
}

char	*find_executable_in_path(char **path_array, const char *cmd)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = 0;
	while (path_array[i])
	{
		cmd_path = construct_full_path(path_array[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (NULL);
}

char	**get_path_env(t_mini *obj)
{
	t_list_e	*env_temp;
	char		**path_array;

	env_temp = obj->env;
	path_array = NULL;
	while (env_temp)
	{
		if (ft_strncmp(env_temp->content, "PATH=", 5) == 0)
		{
			path_array = split_string_by_delimiter(env_temp->content + 5, ':');
			break ;
		}
		env_temp = env_temp->next;
	}
	if (!path_array)
	{
		perror(ERROR_PATH);
		exit(set_and_return_exit_code(obj, EXIT_FAILURE));
	}
	return (path_array);
}

char	*get_command_path(t_mini *obj, const char *cmd)
{
	char	**path_array;
	char	*cmd_path;

	path_array = get_path_env(obj);
	cmd_path = find_executable_in_path(path_array, cmd);
	if (!cmd_path)
	{
		perror(CMD_N_F);
		exit(set_and_return_exit_code(obj, EXIT_FAILURE));
	}
	return (cmd_path);
}

void	child_process_execute(t_mini *obj, t_list_c *current_cmd, char **env)
{
	char	*full_path;

	full_path = NULL;
	if (access(current_cmd->content[0], X_OK) == 0)
		full_path = current_cmd->content[0];
	else
		full_path = get_command_path(obj, current_cmd->content[0]);
	execve(full_path, current_cmd->content, env);
	perror("execve error");
	free(full_path);
	exit(set_and_return_exit_code(obj, EXIT_FAILURE));
}
