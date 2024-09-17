/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:14 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 15:27:33 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command_list(t_list_c **command_list)
{
	t_list_c	*next;
	t_list_c	*current;

	if (command_list == NULL || *command_list == NULL)
		return ;
	current = *command_list;
	while (current != NULL)
	{
		next = current->f_ward;
		free_command_node(current);
	}
	*command_list = NULL;
}

void	exit_free(t_mini *shell)
{
	clear_inf_list(&shell->inf);
	if (shell->old_work_dir)
	{
		free(shell->old_work_dir);
		shell->old_work_dir = NULL;
	}
	if (shell->work_dir)
	{
		free(shell->work_dir);
		shell->work_dir = NULL;
	}
}


static bool	is_numeric(const char *line)
{
	if (*line == '\0')
		return (false);
	while (*line)
	{
		if (!isdigit(*line))
			return (false);
		line++;
	}
	return (true);
}

static void	exit_with_error(t_mini *shell, int error_code, char *msg)
{
	printf("%s", msg);
	exit_free(shell);
	exit(set_and_return_drop_num(shell, error_code));
}

int	built_exit(t_mini *shell, char *argv[])
{
	int	arg_count;

	arg_count = 0;
	while (argv[arg_count])
		arg_count++;
	if (arg_count > 2)
		exit_with_error(shell, 130, EXIT_ERORR_MANY);
	if (arg_count == 2)
	{
		if (is_numeric(argv[1]) == false)
			exit_with_error(shell, 130, EXIT_ERORR_NUMERIC);
		else
			shell->drop_num = atoi(argv[1]);
	}
	exit_free(shell);
	printf(EXIT);
	exit(shell->drop_num);
}
