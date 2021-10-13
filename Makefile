CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror
INCLUDE = -I./includes
LDFLAGS = -L./src/queue -L./src/libft
LIBS	= -lq -lft -ltermcap
LIBQ	= libqueue.a
LIBFT 	= libft.a
NAME 	= minishell
SRCS = \
	src/lexer/lexer.c \
	src/lexer/literal/literal.c \
	src/lexer/literal/quoting.c \
	src/lexer/metacharacter/metacharacter.c \
	src/lexer/literal/wildcard.c \
	src/parser/parser.c \
	src/interpreter/interpreter.c \
	src/interpreter/pipeline.c \
	src/interpreter/simple_command.c \
	src/interpreter/execute_cmds.c \
	src/interpreter/execute_bltin.c \
	src/interpreter/assign_variable.c \
	src/interpreter/expansion.c \
	src/interpreter/redirect.c \
	src/interpreter/here_documents.c \
	src/interpreter/signal.c \
	src/shell_variable/get_shell_var.c \
	src/shell_variable/set_shell_var.c \
	src/shell_variable/new_shell_var.c \
	src/shell_variable/get_param_elem.c \
	src/shell_variable/get_next_line.c \
	src/shell_variable/hash.c \
	src/prompt/prompt.c \
	src/prompt/prompt_utils.c \
	src/prompt/copy_and_paste.c \
	src/prompt/move.c \
	src/prompt/history.c \
	src/bltin/cd.c \
	src/bltin/cd_path.c\
	src/bltin/echo.c \
	src/bltin/pwd.c \
	src/bltin/unset.c \
	src/bltin/export.c \
	src/bltin/exit.c \
	src/bltin/env.c \
	src/error/error.c \
	src/free/free.c \
	src/util/set_environ.c \
	src/minishell.c

OBJS=$(SRCS:.c=.o)

NAME_LEAKS	:= minishell_leaks
SRCS_LEAKS	:= src/leaks.c
OBJS_LEAKS	:= $(SRCS_LEAKS:.c=.o)

all: $(NAME)

leaks: $(OBJS) $(OBJS_LEAKS) $(LIBFT) $(LIBQ)
	$(CC) $(CFLAGS) -o $(NAME_LEAKS) $(LDFLAGS) $(OBJS) $(OBJSS_LEAKS) $(LIBS)

clean:
	$(MAKE) clean -C ./src/libft
	$(MAKE) clean -C ./src/queue
	rm -rf $(OBJS)
	rm -rf $(OBJS_LEAKS)

fclean: clean
	$(MAKE) fclean -C ./src/libft
	$(MAKE) fclean -C ./src/queue
	rm -rf $(NAME)
	rm -rf $(NAME_LEAKS)

re:	fclean all


$(NAME): $(OBJS) $(LIBFT) $(LIBQ)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -C ./src/libft

$(LIBQ):
	$(MAKE) -C ./src/queue

.PHONY: clear fclean re all
