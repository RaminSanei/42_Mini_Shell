/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:23:40 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_list *elem)
{
	if (elem->kind == PIPE)
	{
		if (!elem->f_ward || !elem->b_ward || elem->f_ward->kind == PIPE)
			return (ERROR_UNEXPECTED_PIPE);
	}
	return (EXIT_SUCCESS);
}

int	check_invalid_syntax(t_list *elem)
{
	if ((ft_strchr(elem->content, 34) == NULL && ft_strchr(elem->content,
				39) == NULL) && (ft_strstr(elem->content, ">>>")
			|| ft_strstr(elem->content, "<<<")))
		return (ERROR_INVALID_SYNTAX);
	return (EXIT_SUCCESS);
}

int	analyze_redirection(t_list *elem)
{
	int	result;

	while (elem)
	{
		result = check_pipe_syntax(elem);
		if (result != EXIT_SUCCESS)
			return (result);
		result = check_redirection_syntax(elem);
		if (result != EXIT_SUCCESS)
			return (result);
		result = check_invalid_syntax(elem);
		if (result != EXIT_SUCCESS)
			return (result);
		elem = elem->f_ward;
	}
	return (EXIT_SUCCESS);
}

int	check_all_redirection_syntax(t_list *elem)
{
	int	redirection_status;

	redirection_status = analyze_redirection(elem);
	if (redirection_status == ERROR_UNEXPECTED_NEWLINE)
	{
		printf(ERROR_UNEX_NLINE);
		return (EXIT_FAILURE);
	}
	else if (redirection_status == ERROR_UNEXPECTED_PIPE)
	{
		printf(ERROR_UNEX_PIPE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_syntax(t_list *elem)
{
	if (check_all_redirection_syntax(elem) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
