/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:41:18 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/09 18:55:04 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_mini
{
	char	*line;
	char	*pwd;
	char	*oldpwd;
	int		exit_num;
	char	**env;
}			t_mini;

void		sigint_handler(int signal);

// libft functions
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);

#endif