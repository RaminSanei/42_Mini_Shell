/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/10 11:21:12 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	close_file_descriptor(int fd)
{
	if (fd >= 0)
	{
		close(fd);
	}
}

int	setup_redirection(const char *file_path, int flags, int mode, int target_fd)
{
	int	fd;

	fd = open(file_path, flags, mode);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell error: unable to open file\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, target_fd) < 0)
	{
		ft_putstr_fd("Minishell error: redirection failed\n", STDERR_FILENO);
		close_file_descriptor(fd);
		return (EXIT_FAILURE);
	}
	close_file_descriptor(fd);
	return (EXIT_SUCCESS);
}

int	set_input_redirection(t_list_l *red)
{
	return (setup_redirection(red->content, O_RDONLY, 0, STDIN_FILENO));
}

int	handle_append_redirection(t_list_l *red)
{
	return (setup_redirection(red->content, O_CREAT | O_WRONLY | O_APPEND, 0644,
			STDOUT_FILENO));
}

int	handle_truncate_redirection(t_list_l *red)
{
	return (setup_redirection(red->content, O_CREAT | O_WRONLY | O_TRUNC, 0644,
			STDOUT_FILENO));
}

int	handle_input_redirection(t_list_l *lexer_node)
{
	if (set_input_redirection(lexer_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_append_redirection(t_list_l *lexer_node)
{
	if (set_append_redirection(lexer_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
int	handle_truncate_redirection(t_list_l *lexer_node)
{
	if (set_truncate_redirection(lexer_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	apply_redirections(t_list_c *command)
{
	t_list_l	*current_lexer_node;

	if (command == NULL)
		return (EXIT_SUCCESS);
	current_lexer_node = command->lexer;
	while (current_lexer_node)
	{
		if (current_lexer_node->index == TRUNC)
		{
			if (handle_truncate_redirection(current_lexer_node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (current_lexer_node->index == APPEND)
		{
			if (handle_append_redirection(current_lexer_node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (current_lexer_node->index == INPUT
			|| current_lexer_node->index == HEREDOC)
		{
			if (handle_input_redirection(current_lexer_node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		current_lexer_node = current_lexer_node->next;
	}
	return (EXIT_SUCCESS);
}
