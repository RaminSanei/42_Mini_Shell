/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:11:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_export_error(const char *arg)
{
	printf(INVALID_CTX " %s\n", arg);
}

int	process_export_arg(t_mini *shell, char *arg)
{
	int	equal_position;

	equal_position = find_key_length(arg);
	if (equal_position == MINUS1)
	{
		handle_export_error(arg);
		return (MINUS1);
	}
	else if (equal_position != 0)
	{
		set_environment_variable(arg, &shell->inf);
	}
	return (EXIT_SUCCESS);
}

int	built_export(t_mini *shell, char *argv[])
{
	int	k;

	k = 1;
	if (argv[1] == NULL)
	{
		built_env(shell, argv);
		return (EXIT_SUCCESS);
	}
	while (argv[k] != NULL)
	{
		if (process_export_arg(shell, argv[k]) == MINUS1)
			return (MINUS1);
		k++;
	}
	return (EXIT_SUCCESS);
}
