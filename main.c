/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:28 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/05 14:53:28 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell_env(t_mini *shell, char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	shell->env = env;
	shell->pwd = ft_strdup(pwd);
	shell->oldpwd = ft_strdup(pwd);
	shell->exit_num = 0;
}

int	main(int argc, char *argv[], char *env[])
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
				write(2, EXIT, 5);
				break ;
			}
			else if (shell.line[0] != '\0')
			{
				add_history(shell.line);
				parse_input(&shell);
			}
		}
	}
	else
	{
		printf(ERROR_NO_ARG);
		return (EXIT_FAILURE * -1);
	}
	return (EXIT_SUCCESS);
}
