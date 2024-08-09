/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:28 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/09 18:32:02 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell_env(t_mini *shell, char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	(shell)->env = env;
	(shell)->pwd = ft_strdup(pwd);
	(shell)->oldpwd = ft_strdup(pwd);
	(shell)->exit_num = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_mini	shell;

	if (argc == 1)
	{
		initialize_shell_env(&shell, env);
		while (1)
		{
			signal(SIGINT, sigint_handler);
			signal(SIGQUIT, SIG_IGN);
			shell.line = readline("@minishell> $ ");
			if (!shell.line)
			{
				write(2, "exit\n", 5);
				break ;
			}
			else if (shell.line[0] != '\0')
			{
				add_history(shell.line);
			}
		}
	}
	else
	{
		printf("Error: there is no arguments.\n");
		return (-1);
	}
	return (EXIT_SUCCESS);
}
