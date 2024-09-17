/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_streams.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 09:09:15 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_stream(t_list_l *scanner_node)
{
	if (configure_input_stream(scanner_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_append_stream(t_list_l *scanner_node)
{
	if (configure_append_stream(scanner_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_truncate_stream(t_list_l *scanner_node)
{
	if (configure_truncate_stream(scanner_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	configure_streams_helper(t_list_l *current_scanner_node)
{
	if (current_scanner_node->type == TRUNC)
	{
		if (handle_truncate_stream(current_scanner_node) == EXIT_FAILURE)
			return (130);
	}
	else if (current_scanner_node->type == APPEND)
	{
		if (handle_append_stream(current_scanner_node) == EXIT_FAILURE)
			return (130);
	}
	else if (current_scanner_node->type == INPUT
		|| current_scanner_node->type == HEREDOC)
	{
		if (handle_input_stream(current_scanner_node) == EXIT_FAILURE)
			return (130);
	}
	return (EXIT_SUCCESS);
}

int	configure_streams(t_list_c *action)
{
	t_list_l	*current_scanner_node;

	if (action == NULL)
		return (EXIT_SUCCESS);
	current_scanner_node = action->scanner;
	while (current_scanner_node)
	{
		if (configure_streams_helper(current_scanner_node) == 130)
			return (130);
		current_scanner_node = current_scanner_node->f_ward;
	}
	return (EXIT_SUCCESS);
}
