/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:06:12 by ssanei            #+#    #+#             */
/*   Updated: 2024/08/31 13:47:40 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	check_pipe_syntax(t_list *toks)
{
	if (toks->t_type == PIPE)
	{
		if (!toks->next || !toks->prev || toks->next->t_type == PIPE)
			return (ERROR_UNEXPECTED_PIPE);
	}
	return (EXIT_SUCCESS);
}

int	check_redirection_syntax(t_list *toks)
{
	if ((toks->t_type == APPEND || toks->t_type == INPUT
			|| toks->t_type == TRUNC || toks->t_type == HEREDOC) && (!toks->next
			|| toks->next->t_type > ARG))
		return (ERROR_UNEXPECTED_NEWLINE);
	return (EXIT_SUCCESS);
}

int	check_invalid_syntax(t_list *toks)
{
	if ((ft_strchr(toks->content, 34) == NULL && ft_strchr(toks->content,
				39) == NULL) && (ft_strstr(toks->content, ">>>")
			|| ft_strstr(toks->content, "<<<")))
		return (ERROR_INVALID_SYNTAX);
	return (EXIT_SUCCESS);
}

int	analyze_redirection(t_list *toks)
{
	int	result;

	while (toks)
	{
		result = check_pipe_syntax(toks);
		if (result != EXIT_SUCCESS)
			return (result);
		result = check_redirection_syntax(toks);
		if (result != EXIT_SUCCESS)
			return (result);
		result = check_invalid_syntax(toks);
		if (result != EXIT_SUCCESS)
			return (result);
		toks = toks->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redirection_syntax(t_list *toks)
{
	int	redirection_status;

	redirection_status = analyze_redirection(toks);
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

int	validate_syntax(t_list *toks)
{
	if (check_redirection_syntax(toks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
