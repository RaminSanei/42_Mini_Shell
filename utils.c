/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:09:01 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 17:59:32 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	are_strings_equal(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

int	set_and_return_drop_num(t_mini *shell, int code)
{
	if (shell)
		shell->drop_num = code;
	return (code);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

///// 1. handle_error_int for dup and fork
int	handle_error_int(t_mini *shell, int result, const char *error_msg)
{
	if (result == -1)
	{
		ft_putstr_fd("minishell error: ", STDERR_FILENO);
		perror(error_msg);
		exit(set_and_return_drop_num(shell, 130));
	}
	return (result);
}

///// 2. handle_error_void for dup2 and pipe
void	handle_error_void(t_mini *shell, int result, const char *error_msg)
{
	if (result == -1)
	{
		ft_putstr_fd("minishell error: ", STDERR_FILENO);
		perror(error_msg);
		exit(set_and_return_drop_num(shell, 130));
	}
}

