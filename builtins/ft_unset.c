/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:40 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:14:52 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_node_from_list(t_list_e **node)
{
	t_list_e	*to_remove;

	if (node == NULL || *node == NULL)
		return ;
	to_remove = *node;
	if (to_remove->b_ward == NULL)
	{
		*node = to_remove->f_ward;
		if (to_remove->f_ward)
			to_remove->f_ward->b_ward = NULL;
	}
	else if (to_remove->f_ward == NULL)
		to_remove->b_ward->f_ward = NULL;
	else
	{
		to_remove->b_ward->f_ward = to_remove->f_ward;
		to_remove->f_ward->b_ward = to_remove->b_ward;
	}
	free(to_remove);
}

void	discard_inf_entry(const char *line, t_list_e **inf)
{
	t_list_e	*inf_t;
	size_t		str_len;
	int			match;

	inf_t = *inf;
	str_len = strlen(line);
	while (inf_t)
	{
		match = find_key_length(inf_t->content);
		if (match != MINUS1 && strncmp(line, inf_t->content, str_len) == 0
			&& strncmp(inf_t->content, line, match) == 0)
		{
			delete_node_from_list(&inf_t);
			return ;
		}
		inf_t = inf_t->f_ward;
	}
}

void	handle_unset_error(const char *arg, const char *message)
{
	printf("unset: %s: %s\n", arg, message);
}

int	process_unset_arg(t_mini *shell, char *arg)
{
	int	equal_position;

	equal_position = find_key_length(arg);
	if (equal_position > 0)
	{
		handle_unset_error(arg, INV_PARAM_NAME);
		return (MINUS1);
	}
	else if (equal_position == MINUS1)
	{
		handle_unset_error(arg, INV_CTX);
		return (MINUS1);
	}
	discard_inf_entry(arg, &shell->inf);
	return (EXIT_SUCCESS);
}

int	built_unset(t_mini *shell, char *argv[])
{
	int	k;

	k = 1;
	while (argv[k])
	{
		if (process_unset_arg(shell, argv[k]) == MINUS1)
			return (MINUS1);
		k++;
	}
	return (EXIT_SUCCESS);
}
