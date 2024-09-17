/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:41:18 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/17 18:27:00 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// messages
# define ERROR_OPEN_QUOTE "minishell: syntax error with open quotes\n"
# define ERROR_NO_ARG "Error: there is no arguments.\n"
# define ERROR_EXE "execve error"
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
# define INV_PARAM_NAME "invalid parameter name"
# define INV_CTX "not valid in this context"
# define UN_OPN_FILE "Minishell error: unable to open file\n"
# define STREAM_FAIL "Minishell error: stream routing failed\n"

// error numbers
# define MINUS1 -1
# define ERROR_UNEXPECTED_PIPE -2
# define ERROR_UNEXPECTED_NEWLINE -3
# define ERROR_INVALID_SYNTAX -4
# define NUM_B_CMD 7
# define ERROR130 130
# define PWD_BUFFER_SIZE 200

// extern int				drop_num;

typedef enum e_action_type
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
}						t_action_type;

typedef struct s_list_l
{
	char				*content;
	struct s_list_l		*f_ward;
	enum e_action_type	type;
}						t_list_l;

typedef struct s_list_e
{
	char				*content;
	struct s_list_e		*b_ward;
	struct s_list_e		*f_ward;
}						t_list_e;

typedef struct s_list
{
	char				*content;
	enum e_action_type	kind;
	struct s_list		*b_ward;
	struct s_list		*f_ward;
}						t_list;

typedef struct s_list_c
{
	char				**content;
	t_list_l			*scanner;
	struct s_list_c		*b_ward;
	struct s_list_c		*f_ward;
}						t_list_c;

typedef struct s_mini
{
	char				*line;
	char				*work_dir;
	char				*old_work_dir;
	int					drop_num;
	t_list				*elem;
	t_list_e			*inf;
	t_list_c			*c_list;
	int					*process_num;
}						t_mini;

////////////////////////////////////////////////////////////////////////////////
typedef int				(*t_act_func)(t_mini *shell, char *argv[]);

typedef struct s_builtin_c
{
	char				*name;
	t_act_func			function;
}						t_builtin_c;
//////////////////////////////////// libft functions////////////////////////////
char					*ft_strdup(char *s1);
size_t					ft_strlen(const char *str);
void					ft_putstr_fd(char *s, int fd);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strchr(const char *str, int c);
char					*ft_strrchr(const char *str, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnjoin(char *s1, char *s2, int flag);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin(char *s1, char *s2);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
char					**ft_split(char *s, char c);
void					*ft_calloc(size_t count, size_t size);
char					*ft_itoa(int n);

//////////////////////////////////// mini_shell functions//////////////////
void					handle_interrupt(int signal);
void					parse_input(t_mini *shell);
int						set_and_return_drop_num(t_mini *shell, int code);
void					*safe_malloc(size_t size);
void					erase_pointer_array(char **array);
void					skip_whitespace(char **input);
bool					is_separator(char **line, char quote_char);
int						allocate_memory_for_action(char *input);
bool					are_strings_equal(char *s1, char *s2);
int						validate_quotes(t_mini *shell);
int						validate_syntax(t_list *elem);
void					perform_expansion(t_mini *shell);
t_list_c				*build_action_list(t_list *elem);
void					run_action_execution(t_mini *shell, char **inf);
void					handle_heredoc(t_mini *shell);
bool					is_builtin_action(char **action);
char					*retrieve_inf_value(t_mini *shell, const char *key);
void					init_builtin_act(t_builtin_c actions[]);
void					set_environment_variable(char *line, t_list_e **inf);
int						find_key_length(const char *line);
void					add_inf_variable(t_list_e **inf, char *line);
int						built_cd(t_mini *shell, char *argv[]);
int						built_echo(t_mini *shell, char *argv[]);
int						built_env(t_mini *shell, char *argv[]);
int						built_exit(t_mini *shell, char *argv[]);
int						built_export(t_mini *shell, char *argv[]);
int						built_pwd(t_mini *shell, char *argv[]);
int						built_unset(t_mini *shell, char *argv[]);
void					free_string_array(char *array[]);
void					init_builtin_act(t_builtin_c actions[]);
int						configure_streams(t_list_c *action);
int						execute_builtin_action(t_mini *shell, char *argv[]);
void					safely_close_file_descriptors(int descriptor1,
							int descriptor2);
void					handle_error_void(t_mini *shell, int result,
							const char *error_msg);
int						handle_error_int(t_mini *shell, int result,
							const char *error_msg);
void					run_execution_loop(t_mini *shell, int main_fd_in,
							int main_fd_out, char **inf);
int						get_action_count(t_mini *shell);
void					handle_child_operation(t_mini *shell,
							t_list_c *current_act, char **inf);
void					execute_child_task(t_mini *shell, t_list_c *current_act,
							int pipe_fds[2], char **inf);
char					**split_string_by_delimiter(const char *line,
							char delimiter);
void					execute_parent_task(t_mini *shell,
							t_list_c *current_act, int pipe_fds[2]);
void					wait_for_all_processes(t_mini *shell, int *exit_status);
int						handle_cd_error(char *path);
void					cleanup_temp_files(void);
void					free_scanner_list(t_list_l **scanner);
void					free_action_node(t_list_c *action_node);
int						delete_file(char *file);
char					*generate_tmp_filename(int index);
void					clear_inf_list(t_list_e **inf);
void					free_inf_node(t_list_e *node);
int						configure_stream_routing(const char *file_path,
							int flags, int mode, int target_fd);
void					free_command_node(t_list_c *command_node);
void					built_cd_erase_doub(t_mini *shell, char *argv[]);
bool					is_delimiter(char c);
int						ignore_chars(char **line, int *number);
void					parse_symbol_pairs(int *number, char **line);
void					cleanup_string_list(char **string_array,
							int num_elements);
bool					is_dollar_sequence(char **line);
int						determine_length(char *line, char delimiter);
int						count_arguments(t_list *elem);
char					**allocate_arguments(t_list *elem);
int						configure_input_stream(t_list_l *red);
int						configure_append_stream(t_list_l *red);
int						configure_truncate_stream(t_list_l *red);
char					*construct_full_address_helper(const char *adr_element,
							const char *action, int adr_len, int ac_len);
void					initialize_shell_inf(t_mini *shell, char **inf);
void					ft_free_split(char **actions);
char					*expand_line(t_mini *shell, char *line);
void					write_file_contents(int fd, t_mini *shell,
							char *stop_word);
char					*generate_file_name(int index);
char					*handle_special_cases(const char *key, int drop_num);
void					expand_word(t_mini *shell, t_list *elem,
							char **arguments, int *index);
char					*expand_action(t_mini *shell, char *action);
bool					check_unclosed_quotes(const char *line);
t_list					*generate_actions(char **input);
int						check_redirection_syntax(t_list *elem);
#endif