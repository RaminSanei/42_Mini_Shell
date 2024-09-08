/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/08 09:55:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **tokens)
{
	char	**temp;

	if (!tokens)
		return ;
	temp = tokens;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(tokens);
}

char	*expand_line(t_mini *shell, char *line)
{
	char	**tokens;
	char	*expanded_line;
	int		i;

	if (!line || ft_strcmp(line, "") == 0)
		return (ft_strdup(""));
	tokens = ft_split(line, ' ');
	free(line);
	expanded_line = NULL;
	i = 0;
	while (tokens[i])
	{
		if (ft_strrchr(tokens[i], '$'))
			expanded_line = ft_strnjoin(expanded_line, get_value(shell,
						tokens[i] + 1), 2);
		else
			expanded_line = ft_strnjoin(expanded_line, tokens[i], 2);
		i++;
	}
	expanded_line = ft_strnjoin(expanded_line, "\n", 1);
	ft_free_split(tokens);
	return (expanded_line);
}

void	write_file_contents(int fd, t_mini *shell, const char *stop_word)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, stop_word) == 0)
		{
			free(line);
			break ;
		}
		line = expand_line(shell, line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

char	*generate_file_name(int index)
{
	return (ft_strnjoin("heredoc_", ft_itoa(index), 3));
}

char	*create_heredoc_file(t_mini *shell, const char *delimiter, int index)
{
	char	*file_name;
	int		fd;

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
	close(fd);
	return (file_name);
}

void	update_lexer_string(t_list_l *lexer, const char *file_path)
{
	char	*new_str;

	if (lexer->content)
	{
		new_str = ft_strnjoin(lexer->content, file_path, 4);
		free(lexer->content);
		lexer->content = new_str;
	}
}

void	handle_heredoc_token(t_list_l *lexer, t_mini *shell, int index)
{
	char	*file_path;

	file_path = create_heredoc_file(shell, lexer->content, index);
	if (file_path)
	{
		update_lexer_string(lexer, file_path);
		free(file_path);
	}
}

void	process_command_heredocs(t_list_c *cmd, t_mini *shell, int *index)
{
	t_list_l	*lexer;

	lexer = cmd->lexer;
	while (lexer)
	{
		if (lexer->index == HEREDOC)
		{
			handle_heredoc_token(lexer, shell, *index);
			(*index)++;
		}
		lexer = lexer->next;
	}
}

void	handle_heredoc(t_mini *shell)
{
	t_list_l	*lexer;
	int			i;
	t_list_c	*cmd;

	i = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		process_command_heredocs(cmd, shell, &i);
		cmd = cmd->next;
	}
}
