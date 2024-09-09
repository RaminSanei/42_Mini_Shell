/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:43 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 12:43:57 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/////////////add_env_variable/////////////
static t_list_e	*create_env_node(const char *str, t_list_e *prev)
{
	t_list_e	*new_node;

	new_node = safe_malloc(sizeof(t_list_e));
	new_node->content = ft_strdup(str);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->prev = prev;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_variable(t_list_e **env, const char *str)
{
	t_list_e	*current;
	t_list_e	*new_node;

	current = *env;
	if (!current)
	{
		new_node = create_env_node(str, NULL);
		if (new_node)
			*env = new_node;
	}
	else
	{
		while (current->next)
			current = current->next;
		new_node = create_env_node(str, current);
		if (new_node)
			current->next = new_node;
	}
}

/////////////set_environment_variable/////////////

static int	is_key_match(const char *env_value, const char *str)
{
	int	key_len;

	key_len = find_key_length(str);
	return (ft_strncmp(str, env_value, key_len) == 0);
}

static void	update_existing_env(t_list_e *env_t, char *str)
{
	free(env_t->content);
	env_t->content = ft_strdup(str);
}

void	set_environment_variable(char *str, t_list_e **env)
{
	t_list_e	*env_t;

	env_t = *env;
	while (env_t)
	{
		if (is_key_match(env_t->content, str))
		{
			update_existing_env(env_t, str);
			return ;
		}
		env_t = env_t->next;
	}
	add_env_variable(env, str);
}
