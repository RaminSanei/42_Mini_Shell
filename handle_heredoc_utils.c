/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 15:32:05 by ssanei           ###   ########.fr       */
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
		else if (!ft_strcmp(line, stop_word))
		{
			free(line);
			close(fd);
			stop = true;
		}
		line = expand_line(shell, line);
		write(fd, line, ft_strlen(line));
	}
}

char	*generate_file_name(int index)
{
	return (ft_strnjoin("heredoc_", ft_itoa(index), 3));
}
