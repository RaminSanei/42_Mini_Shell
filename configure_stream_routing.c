/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_streams.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 09:09:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(const char *file_path, int flags, int mode)
{
	int	file_channel;

	file_channel = open(file_path, flags, mode);
	if (file_channel < 0)
		ft_putstr_fd(UN_OPN_FILE, STDERR_FILENO);
	return (file_channel);
}

int	duplicate_fd(int source_fd, int target_fd)
{
	if (dup2(source_fd, target_fd) < 0)
	{
		ft_putstr_fd(STREAM_FAIL, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	configure_stream_routing(const char *file_path, int flags, int mode,
		int target_fd)
{
	int	file_channel;

	file_channel = open_file(file_path, flags, mode);
	if (file_channel < 0)
		return (EXIT_FAILURE);
	if (duplicate_fd(file_channel, target_fd) == EXIT_FAILURE)
	{
		close(file_channel);
		return (EXIT_FAILURE);
	}
	close(file_channel);
	return (EXIT_SUCCESS);
}
