/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:40 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/10 10:22:36 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_remove_node(t_list_e **node)
{
	t_list_e	*to_remove;

	if (node == NULL || *node == NULL)
		return ;
	to_remove = *node;
	if (to_remove->prev == NULL)
	{
		*node = to_remove->next;
		if (to_remove->next)
			to_remove->next->prev = NULL;
	}
	else if (to_remove->next == NULL)
		to_remove->prev->next = NULL;
	else
	{
		to_remove->prev->next = to_remove->next;
		to_remove->next->prev = to_remove->prev;
	}
	free(to_remove);
}

void	delete_env(const char *str, t_list_e **env)
{
	t_list_e	*env_t;
	size_t		str_len;
	int			equal;

	env_t = *env;
	str_len = strlen(str);
	while (env_t)
	{
		equal = find_key_length(env_t->content);
		if (equal != -1 && strncmp(str, env_t->content, str_len) == 0
			&& strncmp(env_t->content, str, equal) == 0)
		{
			ft_remove_node(&env_t);
			return ;
		}
		env_t = env_t->next;
	}
}
///////////////////////////////////////////////
void	handle_unset_error(const char *arg, const char *message)
{
	printf("unset: %s: %s\n", arg, message);
}

int	process_unset_arg(t_mini *obj, const char *arg)
{
	int	equal_position;

	equal_position = find_key_length(arg);
	if (equal_position > 0)
	{
		handle_unset_error(arg, "invalid parameter name");
		return (MINUS1);
	}
	else if (equal_position == -1)
	{
		handle_unset_error(arg, "not valid in this context");
		return (MINUS1);
	}
	delete_env(arg, &obj->env);
	return (EXIT_SUCCESS);
}

int	ft_unset(t_mini *obj, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (process_unset_arg(argv[i], obj) == MINUS1)
			return (MINUS1);
		i++;
	}
	return (EXIT_SUCCESS);
}
