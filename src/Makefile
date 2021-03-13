CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = \
	cd \
	pwd \
	env \
	echo \
	exit \
	unset \
	export \
	minishell
MINISHELL_SRC = \
			lexer/lexer.c \
			lexer/parameter.c \
			lexer/quoting.c \
			lexer/metacharacter.c \
			parser/parser.c \
			parser/fetch_path.c \
			get_next_line_for_minishell.c \
			error.c \
			minishell.c
MINISHELL_OBJ=$(MINISHELL_SRC:.c=.o)

all: libft/libft.a $(NAME)

clean:
	$(MAKE) clean -C ./libft
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re:	fclean all

minishell: $(MINISHELL_OBJ)
	$(CC) $(CFLAGS) -o $@ -L./libft $^ -lft
cd: cd.c
	$(CC) $(CFLAGS) -o $@ -L./libft $< -lft
pwd: pwd.c
	$(CC) $(CFLAGS) -o $@ $<
env: env.c
	$(CC) $(CFLAGS) -o $@ $<
echo: echo.c
	$(CC) $(CFLAGS) -o $@ $<
exit: exit.c
	$(CC) $(CFLAGS) -o $@ $<
unset: unset.c
	$(CC) $(CFLAGS) -o $@ $<
export: export.c
	$(CC) $(CFLAGS) -o $@ $<
libft/libft.a:
	$(MAKE) -C ./libft

.PHONY: clear fclean re all
