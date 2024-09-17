/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:43 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 13:17:00 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_cd_error(char *path)
{
	printf(ERROR_DIR "%s\n", path);
	return (MINUS1);
}

void	cleanup_temp_files(void)
{
	char	*file;
	int		k;

	k = 0;
	while (1)
	{
		file = generate_tmp_filename(k);
		if (delete_file(file) == MINUS1)
		{
			free(file);
			break ;
		}
	}
	free(file);
	k++;
}

void	free_scanner_list(t_list_l **scanner)
{
	t_list_l	*current;
	t_list_l	*next;

	if (scanner == NULL || *scanner == NULL)
		return ;
	current = *scanner;
	while (current != NULL)
	{
		next = current->f_ward;
		free(current->content);
		free(current);
		current = next;
	}
	*scanner = NULL;
}

void	free_string_array(char *array[])
{
	int	k;

	if (array == NULL)
		return ;
	k = 0;
	while (array[k] != NULL)
	{
		free(array[k]);
		k++;
	}
	free(array);
}

void	built_cd_erase_doub(t_mini *shell, char *argv[])
{
	free(shell->old_work_dir);
	shell->old_work_dir = ft_strdup(shell->work_dir);
	free(shell->work_dir);
	shell->work_dir = ft_strdup(argv[1]);
}
