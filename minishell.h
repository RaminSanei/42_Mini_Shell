/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:41:18 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/11 19:26:54 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// messages
# define ERROR_OPEN_QUOTE "minishell: syntax error with open quotes\n"
# define ERROR_NO_ARG "Error: there is no arguments.\n"
# define EXIT "exit\n"
# define ERROR_UNEX_NLINE "bash: syntax error near unexpected token `newline'\n"
# define ERROR_UNEX_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERROR_DIR "cd: no such file or directory: "
# define EXIT_ERORR_NUMERIC "exit\nminishell: exit: numeric argument required\n"
# define EXIT_ERORR_MANY "exit: too many arguments.\n"
# define ERROR_GET_DIR "Error getting current working directory"
# define INVALID_CTX "export: not valid in this context:"
# define ERROR_PATH "Could not find PATH variable"
# define CMD_N_F "Command not found: "

// error numbers
# define MINUS1 -1
# define ERROR_UNEXPECTED_PIPE -2
# define ERROR_UNEXPECTED_NEWLINE -3
# define ERROR_INVALID_SYNTAX -4
# define NUM_B_CMD 7
# define ERROR130 130
# define PWD_BUFFER_SIZE 200

typedef enum e_token_type
{
	EMPTY,
	CMD,
	END,
	ARG,
	APPEND,
	INPUT,
	TRUNC,
	HEREDOC,
	PIPE,
}						t_token_type;
////////////////////////////////////////////////////////////////////////////////
typedef int				(*t_cmd_func)(char **argv, t_mini *obj);

typedef struct s_builtin_c
{
	char				*name;
	t_cmd_func			function;
}						t_builtin_c;
////////////////////////////////////////////////////////////////////////////////

typedef struct s_list_c
{
	void				**content;
	t_list_l			*lexer;
	t_list_c			*prev;
	t_list_c			*next;
}						t_list_c;

typedef struct s_list_l
{
	void				*content;
	int					index;
	enum e_token_type	type;
	t_list_l			*next;
}						t_list_l;

typedef struct s_list_e
{
	void				*content;
	t_list_e			*prev;
	t_list_e			*next;
}						t_list_e;

typedef struct s_list
{
	void				*content;
	enum e_token_type	t_type;
	t_list				*prev;
	t_list				*next;
}						t_list;

typedef struct s_mini
{
	char				*line;
	char				*pwd;
	char				*oldpwd;
	int					exit_num;
	t_list				*toks;
	t_list_e			*env;
	t_list_c			*cmd;
	int					*process_id;
}						t_mini;

//////////////////////////////////// libft functions////////////////////////////////////
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *str);
void					ft_putstr_fd(char *s, int fd);
int						strcmp(char *s1, char *s2);
char					*ft_strchr(const char *str, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnjoin(char *s1, char *s2, int flag);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

//////////////////////////////////// libft functions////////////////////////////////////

//////////////////////////////////// mini_shell functions////////////////////////////////////
void					sigint_handler(int signal);
int						parse_input(t_mini *shell);
int						set_and_return_exit_code(t_mini *data, int code);
void					*safe_malloc(size_t size);
void					skip_whitespace(char **input);
bool					is_separator(char **str, char quote_char);
int						allocate_memory_for_token(char *input);
int						validate_quotes(t_mini *shell);
int						validate_syntax(t_list *toks);
void					perform_expansion(t_mini *shell);
t_list_c				*build_command_list(t_list *toks);
int						run_command_execution(t_mini *shell, char **env);
void					handle_heredoc(t_mini *shell);
bool					is_builtin_command(char **command);
void					init_builtin_cmd(t_builtin_c commands[]);
void					set_environment_variable(char *str, t_list_e **env);
int						find_key_length(const char *str);
void					add_env_variable(t_list_e **env, const char *str);
int						ft_cd(t_mini *obj, char *argv[]);
int						ft_echo(t_mini *obj, char *argv[]);
int						ft_env(t_mini *obj, char *argv[]);
int						ft_exit(t_mini *obj, char *argv[]);
int						ft_export(t_mini *obj, char *argv[]);
int						ft_pwd(t_mini *obj, char *argv[]);
int						ft_unset(t_mini *obj, char *argv[]);
void					free_string_array(char *array[]);
void					init_builtin_cmd(t_builtin_c b_commands[]);
int						apply_redirections(t_list_c *command);
int						execute_builtin_command(t_mini *obj, char *argv[]);
void					safely_close_file_descriptors(int descriptor1,
							int descriptor2);
void					handle_error_void(t_mini *shell, int result,
							const char *error_msg);
int						handle_error_int(t_mini *shell, int result,
							const char *error_msg);
void					run_execution_loop(t_mini *obj, int main_fd_in,
							int main_fd_out, char **env);
int						get_command_count(t_mini *obj);
void					child_process_execute(t_mini *obj,
							t_list_c *current_cmd, char **env);
void					execute_child_task(t_mini *data, t_list_c *current_cmd,
							int pipe_fds[2], char **env);
char					**split_string_by_delimiter(const char *str,
							char delimiter);
void					execute_parent_process(t_mini *data,
							t_list_c *current_cmd, int pipe_fds[2]);
int						get_command_count(t_mini *obj);
void					wait_for_all_processes(t_mini *data, int *exit_status);
//////////////////////////////////// mini_shell functions////////////////////////////////////
#endif