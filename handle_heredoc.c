/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 15:39:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_file(t_mini *shell, char *delimiter, int index)
{
	int		fd;
	char	*file_name;

	file_name = generate_file_name(index);
	if (!file_name)
		return (NULL);
	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
	{
		free(file_name);
		return (NULL);
	}
	write_file_contents(fd, shell, delimiter);
	return (file_name);
}

void	update_scanner_string(t_list_l *scanner, char *file_path)
{
	char	*new_str;

	if (scanner->content)
	{
		new_str = ft_strnjoin(scanner->content, file_path, 4);
		free(scanner->content);
		scanner->content = new_str;
	}
}

void	handle_heredoc_action(t_list_l *scanner, t_mini *shell, int index)
{
	char	*file_path;

	file_path = create_heredoc_file(shell, scanner->content, index);
	if (file_path)
	{
		update_scanner_string(scanner, file_path);
		free(file_path);
	}
}

void	process_action_heredocs(t_list_c *c_list, t_mini *shell, int *index)
{
	t_list_l	*scanner;

	scanner = c_list->scanner;
	while (scanner)
	{
		if (scanner->type == HEREDOC)
		{
			handle_heredoc_action(scanner, shell, *index);
			(*index)++;
		}
		scanner = scanner->f_ward;
	}
}

void	handle_heredoc(t_mini *shell)
{
	int			k;
	t_list_c	*c_list;

	k = 0;
	c_list = shell->c_list;
	while (c_list)
	{
		process_action_heredocs(c_list, shell, &k);
		c_list = c_list->f_ward;
	}
}
