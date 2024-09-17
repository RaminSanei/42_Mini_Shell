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

int	configure_input_stream(t_list_l *red)
{
	return (configure_stream_routing(red->content, O_RDONLY, 0, STDIN_FILENO));
}

int	configure_append_stream(t_list_l *red)
{
	return (configure_stream_routing(red->content,
			O_CREAT | O_WRONLY | O_APPEND, 0644, STDOUT_FILENO));
}

int	configure_truncate_stream(t_list_l *red)
{
	return (configure_stream_routing(red->content, O_CREAT | O_WRONLY | O_TRUNC,
			0644, STDOUT_FILENO));
}
