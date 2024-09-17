/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:28 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 18:24:43 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	action_interrupt(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	sub_main(t_mini *shell, char *inf[], bool *stop)
{
	action_interrupt();
	shell->line = readline("@minishell> $ ");
	if (!shell->line)
	{
		write(2, EXIT, 5);
		*stop = true;
	}
	else if (shell->line[0] != '\0')
	{
		add_history(shell->line);
		parse_input(shell);
		run_action_execution(shell, inf);
	}
}

int	main(int argc, char *argv[], char *inf[])
{
	t_mini	shell;
	bool	stop;

	stop = false;
	if (argc == 1 && argv[1] == NULL)
	{
		initialize_shell_inf(&shell, inf);
		while (stop == false)
			sub_main(&shell, inf, &stop);
		free(shell.line);
		free_command_node(shell.c_list);
	}
	else
	{
		printf(ERROR_NO_ARG);
		return (EXIT_FAILURE * -1);
	}
	return (EXIT_SUCCESS);
}
