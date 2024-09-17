/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 13:17:53 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **actions)
{
	char	**temp;

	if (!actions)
		return ;
	temp = actions;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(actions);
}

char	*expand_line(t_mini *shell, char *line)
{
	char	**actions;
	char	*expanded_line;
	int		k;

	if (!line || ft_strcmp(line, "") == 0)
		return (ft_strdup(""));
	actions = ft_split(line, ' ');
	free(line);
	expanded_line = NULL;
	k = 0;
	while (actions[k])
	{
		if (ft_strrchr(actions[k], '$'))
			expanded_line = ft_strnjoin(expanded_line, retrieve_inf_value(shell,
						actions[k] + 1), 2);
		else
			expanded_line = ft_strnjoin(expanded_line, actions[k], 2);
		k++;
	}
	expanded_line = ft_strnjoin(expanded_line, "\n", 1);
	ft_free_split(actions);
	return (expanded_line);
}

void	write_file_contents(int fd, t_mini *shell, char *stop_word)
{
	char	*line;
	bool	stop;

	stop = false;
	while (stop == false)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			stop = true;
		}
		else if (ft_strcmp(line, stop_word) == 0)
		{
			free(line);
			close(fd);
			stop = true;
		}
		line = expand_line(shell, line);
		write(fd, line, ft_strlen(line));
		// free(line);
	}
}

char	*generate_file_name(int index)
{
	return (ft_strnjoin("heredoc_", ft_itoa(index), 3));
}

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
	// close(fd);
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

void	handle_heredoc_token(t_list_l *scanner, t_mini *shell, int index)
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
			handle_heredoc_token(scanner, shell, *index);
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
