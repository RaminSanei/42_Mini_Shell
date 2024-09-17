/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:43 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:32:50 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list_e	*create_inf_node(char *line, t_list_e *b_ward)
{
	t_list_e	*new_node;

	new_node = safe_malloc(sizeof(t_list_e));
	new_node->content = ft_strdup(line);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->b_ward = b_ward;
	new_node->f_ward = NULL;
	return (new_node);
}

void	add_inf_variable(t_list_e **inf, char *line)
{
	t_list_e	*current;
	t_list_e	*new_node;

	current = *inf;
	if (!current)
	{
		new_node = create_inf_node(line, NULL);
		if (new_node)
			*inf = new_node;
	}
	else
	{
		while (current->f_ward)
			current = current->f_ward;
		new_node = create_inf_node(line, current);
		if (new_node)
			current->f_ward = new_node;
	}
}

static int	is_key_match(const char *inf_value, const char *line)
{
	int	key_len;

	key_len = find_key_length(line);
	return (ft_strncmp(line, inf_value, key_len) == 0);
}

static void	update_existing_inf(t_list_e *inf_t, char *line)
{
	free(inf_t->content);
	inf_t->content = ft_strdup(line);
}

void	set_environment_variable(char *line, t_list_e **inf)
{
	t_list_e	*inf_t;

	inf_t = *inf;
	while (inf_t)
	{
		if (is_key_match(inf_t->content, line))
		{
			update_existing_inf(inf_t, line);
			return ;
		}
		inf_t = inf_t->f_ward;
	}
	add_inf_variable(inf, line);
}
