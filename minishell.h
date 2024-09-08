/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:41:18 by ssanei            #+#    #+#             */
/*   Updated: 2024/09/08 09:57:18 by ssanei           ###   ########.fr       */
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

// error numbers
# define MINUS1 -1
# define ERROR_UNEXPECTED_PIPE -2
# define ERROR_UNEXPECTED_NEWLINE -3
# define ERROR_INVALID_SYNTAX -4

typedef enum e_token_type
{
	EMPTY,
	CMD,
	ARG,
	APPEND,
	INPUT,
	TRUNC,
	HEREDOC,
	PIPE,
	END
}						t_token_type;

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
}						t_mini;

void					sigint_handler(int signal);
// int						parsing_input(t_mini *shell);
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

// libft functions
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *str);
void					ft_putstr_fd(char *s, int fd);
int						strcmp(char *s1, char *s2);
char					*ft_strchr(const char *str, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnjoin(char *s1, char *s2, int flag);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

#endif