NAME = minishell

READLINE = -L ~/.brew/opt/readline/lib -lreadline

CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include -g3

CC = cc

SRCS = main.c signal_and_free.c utils.c utils1.c parsing_input.c parsing_utils.c\
	   parsing_expansion.c  handle_heredoc.c is_builtin_action.c execute_parsed_input.c \
   	   execute_parent_task.c execute_child_task.c execute_builtin_action.c action_scanner_list.c \
	   handle_child_operation.c configure_streams.c split_string_by_delimiter.c wait_for_all_processes.c run_execution_loop.c\
	   builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c\
	   builtins/ft_unset.c builtins/set_environment_variable.c builtins/utils.c configure_stream_routing.c builtins/ft_exit_utils.c\
	   helpers/ft_calloc.c helpers/ft_itoa.c helpers/ft_putstr_fd.c helpers/ft_split.c helpers/ft_strchr.c helpers/ft_strcmp.c helpers/ft_strdup.c\
	   helpers/ft_strjoin.c helpers/ft_strlen.c helpers/ft_strncmp.c helpers/ft_strrchr.c helpers/ft_strstr.c helpers/utils_helper_functions.c helpers/determine_length.c\
	   action_scanner_list_utils.c configure_streams_utils.c utils2.c initialize_shell_inf.c handle_heredoc_utils.c helpers/ft_strnjoin.c expand_word.c parsing_input_utils.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READLINE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
