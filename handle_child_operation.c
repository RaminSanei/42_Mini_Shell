/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child_operation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:31 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 16:00:55 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*construct_full_address(const char *adr_element, const char *action)
{
	int		adr_len;
	char	*final_address;
	int		ac_len;

	if (!adr_element || !action)
		return (NULL);
	adr_len = ft_strlen(adr_element);
	ac_len = ft_strlen(action);
	final_address = construct_full_address_helper(adr_element, action, adr_len,
			ac_len);
	return (final_address);
}

char	*find_executable_in_address(char **adr_array, const char *action)
{
	char	*ac_adr;
	int		k;

	ac_adr = NULL;
	k = 0;
	while (adr_array[k])
	{
		ac_adr = construct_full_address(adr_array[k], action);
		if (access(ac_adr, X_OK) == 0)
			return (ac_adr);
		free(ac_adr);
		ac_adr = NULL;
		k++;
	}
	return (NULL);
}

char	**get_address_inf(t_mini *shell)
{
	char		**adr_array;
	t_list_e	*temp_data;

	temp_data = shell->inf;
	adr_array = NULL;
	while (temp_data)
	{
		if (ft_strncmp(temp_data->content, "PATH=", 5) == 0)
		{
			adr_array = split_string_by_delimiter(temp_data->content + 5, ':');
			break ;
		}
		temp_data = temp_data->f_ward;
	}
	if (!adr_array)
	{
		perror(ERROR_PATH);
		exit(set_and_return_drop_num(shell, EXIT_FAILURE));
	}
	return (adr_array);
}

char	*determine_action_address(t_mini *shell, const char *action)
{
	char	**adr_array;
	char	*ac_adr;

	adr_array = get_address_inf(shell);
	ac_adr = find_executable_in_address(adr_array, action);
	if (!ac_adr)
	{
		perror(CMD_N_F);
		exit(set_and_return_drop_num(shell, EXIT_FAILURE));
	}
	return (ac_adr);
}

void	handle_child_operation(t_mini *shell, t_list_c *current_act, char **inf)
{
	char	*final_address;

	final_address = NULL;
	if (access(current_act->content[0], X_OK) == 0)
		final_address = current_act->content[0];
	else
		final_address = determine_action_address(shell,
				current_act->content[0]);
	execve(final_address, current_act->content, inf);
	free(final_address);
	perror(ERROR_EXE);
	exit(set_and_return_drop_num(shell, EXIT_FAILURE));
}
