/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:35 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/15 16:14:39 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_current_directory(char *buffer, size_t size)
{
	if (getcwd(buffer, size) == NULL)
	{
		perror(ERROR_GET_DIR);
		return (MINUS1);
	}
	return (EXIT_SUCCESS);
}

int	handle_pwd(void)
{
	char	path[PWD_BUFFER_SIZE];

	if (get_current_directory(path, sizeof(path)) == EXIT_SUCCESS)
	{
		printf("%s\n", path);
		return (EXIT_SUCCESS);
	}
	return (MINUS1);
}

int	built_pwd(t_mini *shell, char *argv[])
{
	(void)argv;
	(void)shell;
	return (handle_pwd());
}
