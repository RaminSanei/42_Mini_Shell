/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 19:24:05 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	handle_export_error(const char *arg)
{
	printf(INVALID_CTX " %s\n", arg);
}

int	process_export_arg(t_mini *obj, const char *arg)
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
		set_environment_variable(arg, &obj->env);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_mini *obj, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (process_export_arg(obj, argv[i]) == MINUS1)
			return (MINUS1);
		i++;
	}
	return (EXIT_SUCCESS);
}
