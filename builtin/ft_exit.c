/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:46:14 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/09 19:35:32 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

////////////////////////////////////// free_memory_tools////////////////////////////////////

void	free_env_node(t_list_e *node)
{
	if (node == NULL)
		return ;
	free(node->content);
	free(node);
}

void	clear_env_list(t_list_e **env)
{
	t_list_e	*current;
	t_list_e	*next;

	if (env == NULL || *env == NULL)
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
	*env = NULL;
}

// void	clear_env_list(t_list_e ) // TODO
// {
// }
char	*generate_tmp_filename(int index)
{
	return (ft_strnjoin("h", ft_itoa(index), 3));
}

int	delete_file(char *file)
{
	if (unlink(file) == -1)
		return (-1);
	return (0);
}

void	cleanup_temp_files(void)
{
	char	*file;
	int		i;

	i = 0;
	while (1)
	{
		file = generate_tmp_filename(i);
		if (delete_file(file) == MINUS1)
		{
			free(file);
			break ;
		}
	}
	free(file);
	i++;
}

void	free_lexer_list(t_list_l **lexer)
{
	t_list_l	*current;
	t_list_l	*next;

	if (lexer == NULL || *lexer == NULL)
		return ;
	current = *lexer;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*lexer = NULL;
}

void	free_string_array(char *array[])
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_command_node(t_list_c *command_node)
{
	if (command_node == NULL)
		return ;
	free_string_array(command_node->content);
	free_lexer_list(&command_node->lexer);
	free(command_node);
}

void	free_command_list(t_list_c **command_list)
{
	t_list_c	*next;
	t_list_c	*current;

	if (command_list == NULL || *command_list == NULL)
		return ;
	current = *command_list;
	while (current != NULL)
	{
		next = current->next;
		free_command_node(current);
	}
	*command_list = NULL;
}

void	free_tools(t_mini *obj, int n)
{
	if (obj->line)
	{
		free(obj->line);
		obj->line = NULL;
	}
	free_command_list(&obj->cmd);
	cleanup_temp_files();
	if (n != 1)
	{
		clear_env_list(&obj->env);
		if (obj->oldpwd)
		{
			free(obj->oldpwd);
			obj->oldpwd = NULL;
		}
		if (obj->pwd)
		{
			free(obj->pwd);
			obj->pwd = NULL;
		}
	}
}

////////////////////////////////////// ft_exit
//////////////////////////////////////

static bool	is_numeric(const char *str)
{
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (!isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	exit_with_error(t_mini *obj, int error_code, char *msg)
{
	printf(msg);
	free_tools(obj, 2);
	exit(set_and_return_exit_code(obj, error_code));
}

// void	ft_exit(t_mini *obj, char *argv[])
int	ft_exit(t_mini *obj, char *argv[])
{
	int	arg_count;

	arg_count = 0;
	while (argv[arg_count])
		arg_count++;
	if (arg_count > 2)
		exit_with_error(obj, 130, EXIT_ERORR_MANY);
	if (arg_count == 2)
	{
		if (is_numeric(argv[1]) == false)
			exit_with_error(obj, 130, EXIT_ERORR_NUMERIC);
		else
		{
			obj->exit_num = atoi(argv[1]);
		}
	}
	free_tools(obj, 2);
	printf(EXIT);
	exit(obj->exit_num);
}
