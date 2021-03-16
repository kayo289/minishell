CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
INCLUDE = -I../includes
LDFLAGS = -L./builtin -L./libft
LIBS	= -lcmds -lft
NAME 	= minishell
LIBCMDS	= libcmds.so
LIBFT 	= libft.a
CMDS	= cd echo pwd export unset env exit
NAME_SRC = \
	lexer/lexer.c \
	lexer/parameter_expansion.c \
	lexer/quoting.c \
	lexer/metacharacter.c \
	parser/parser.c \
	parser/fetch_path.c \
	get_next_line_for_minishell.c \
	error.c \
	minishell.c
CMDS_SRC = \
	cd.c \
	echo.c \
	pwd.c \
	export.c \
	unset.c \
	env.c \
	exit.c 
NAME_OBJ=$(NAME_SRC:.c=.o)
CMDS_OBJ=$(CMDS_SRC:.c=.o)


all: $(NAME) $(CMDS)

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./builtin
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./builtin
	rm -rf $(NAME)
	rm -rf $(CMDS)

re:	fclean all


$(NAME): $(NAME_OBJ) $(LIBFT) $(LIBCMDS)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(NAME_OBJ) $(LIBS)

cd: cd.o
	$(CC) $(CFLAGS) -o $@ -L./libft $< -lft
pwd: pwd.o
	$(CC) $(CFLAGS) -o $@ $<
env: env.o
	$(CC) $(CFLAGS) -o $@ $<
echo: echo.o
	$(CC) $(CFLAGS) -o $@ $<
exit: exit.o
	$(CC) $(CFLAGS) -o $@ $<
unset: unset.o
	$(CC) $(CFLAGS) -o $@ $<
export: export.o
	$(CC) $(CFLAGS) -o $@ $<
	
$(LIBFT):
	$(MAKE) -C ./libft
$(LIBCMDS):
	$(MAKE) -C ./builtin

.PHONY: clear fclean re all
