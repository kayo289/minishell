SRCS = \
	cd.c \
	env.c \
	pwd.c \
	echo.c \
	exit.c \
	unset.c \
	export.c \
	minishell.c
NAME=$(SRCS:%.c=%)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

clean:
	$(MAKE) clean -C ./libft
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re:fclean all

cd: cd.c
	$(CC) $(CFLAGS) -o $@ $<
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
minishell: minishell.c get_next_line.c libft/libft.a
	$(CC) $(CFLAGS) -o $@ -L./libft $^ -lft
libft/libft.a:
	$(MAKE) -C ./libft

.PHONY: clear fclean re all 
