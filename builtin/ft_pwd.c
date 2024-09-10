/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:35 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/10 09:37:05 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

int	ft_pwd(t_mini *obj, char *argv[])
{
	(void)argv;
	(void)obj;
	return (handle_pwd());
}
