/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:24:32 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/16 15:24:51 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_inf_node(t_list_e *node)
{
	if (node == NULL)
		return ;
	free(node->content);
	free(node);
}

// void	clear_inf_list(t_list_e ) // TODO
void	clear_inf_list(t_list_e **inf)
{
	t_list_e	*current;
	t_list_e	*next;

	if (inf == NULL || *inf == NULL)
		return ;
	current = *inf;
	while (current != NULL)
	{
		next = current->f_ward;
		free_inf_node(current);
		current = next;
	}
	*inf = NULL;
}

char	*generate_tmp_filename(int index)
{
	return (ft_strnjoin("h", ft_itoa(index), 3));
}

int	delete_file(char *file)
{
	if (unlink(file) == MINUS1)
		return (MINUS1);
	return (0);
}

void	free_command_node(t_list_c *command_node)
{
	if (command_node == NULL)
		return ;
	free_string_array(command_node->content);
	free_scanner_list(&command_node->scanner);
	free(command_node);
}