CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
INCLUDE = -I../includes
LDFLAGS = -L./builtin -L./libft
LIBS	= -lcmds -lft -ltermcap
SHELL		= /bin/bash
NAME 	= minishell
CMDS	= \
		cmds/cd \
		cmds/echo \
		cmds/pwd \
		cmds/export \
		cmds/unset \
		cmds/env \
		cmds/exit
LIBCMDS	= libcmds.so
LIBFT 	= libft.a
NAME_SRC = \
	lexer/lexer.c \
	lexer/parameter_expansion.c \
	lexer/quoting.c \
	lexer/metacharacter.c \
	lexer/literal.c \
	parser/parser.c \
	parser/next_token.c \
	parser/assign_variable.c \
	interpreter/interpreter.c \
	interpreter/redirect.c \
	interpreter/command_execute.c \
	interpreter/builtin_execute.c \
	shell_variable/get_shell_var.c \
	shell_variable/set_shell_var.c \
	shell_variable/new_shell_var.c \
	shell_variable/hash.c \
	prompt/prompt.c \
	prompt/prompt_utils.c \
	error/error.c \
	minishell.c
NAME_OBJ=$(NAME_SRC:.c=.o)


all: $(NAME) $(CMDS)
	@source LDPATH_set.sh
	@kill -USR1 `ps h -o %P -p $$PPID`

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./builtin
	$(MAKE) clean -C ./cmds
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./builtin
	$(MAKE) fclean -C ./cmds
	rm -rf $(NAME)
	rm -rf $(CMDS)

re:	fclean all


$(NAME): $(NAME_OBJ) $(LIBFT) $(LIBCMDS)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(NAME_OBJ) $(LIBS)

$(CMDS):
	$(MAKE) -C ./cmds

$(LIBFT):
	$(MAKE) -C ./libft
$(LIBCMDS):
	$(MAKE) -C ./builtin

.PHONY: clear fclean re all
