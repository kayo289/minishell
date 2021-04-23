CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
INCLUDE = -I../includes
LDFLAGS = -L./queue -L./bltin -L./libft
LIBS	= -lqueue -lcmds -lft -ltermcap
NAME 	= minishell
CMDS	= \
		cmds/cd \
		cmds/echo \
		cmds/pwd \
		cmds/export \
		cmds/env \
		cmds/exit
LIBCMDS	= libcmds.so
LIBQUEUE = libqueue.so
LIBFT 	= libft.a
NAME_SRC = \
	lexer/lexer.c \
	lexer/literal/literal.c \
	lexer/literal/expand_parameter.c \
	lexer/literal/quoting.c \
	lexer/metacharacter/metacharacter.c \
	parser/parser.c \
	interpreter/interpreter.c \
	interpreter/signal.c \
	interpreter/redirect.c \
	interpreter/cmd_execute.c \
	interpreter/bltin_execute.c \
	interpreter/assign_variable.c \
	shell_variable/get_shell_var.c \
	shell_variable/set_shell_var.c \
	shell_variable/new_shell_var.c \
	shell_variable/get_next_line.c \
	shell_variable/hash.c \
	prompt/prompt.c \
	prompt/prompt_utils.c \
	prompt/history.c \
	error/error.c \
	minishell.c

NAME_OBJ=$(NAME_SRC:.c=.o)


all: $(NAME) $(CMDS)

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./queue
	$(MAKE) clean -C ./bltin
	$(MAKE) clean -C ./cmds
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./queue
	$(MAKE) fclean -C ./bltin
	$(MAKE) fclean -C ./cmds
	rm -rf $(NAME)
	rm -rf $(CMDS)

re:	fclean all


$(NAME): $(NAME_OBJ) $(LIBFT) $(LIBCMDS) $(LIBQUEUE)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(NAME_OBJ) $(LIBS)

$(CMDS):
	$(MAKE) -C ./cmds

$(LIBFT):
	$(MAKE) -C ./libft

$(LIBQUEUE):
	$(MAKE) -C ./queue

$(LIBCMDS):
	$(MAKE) -C ./bltin

.PHONY: clear fclean re all
