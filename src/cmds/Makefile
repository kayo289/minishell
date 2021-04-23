CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
LDFLAGS = -L../libft
LIBS	= -lft
NAME	= cd echo pwd env
LIBFT 	= libft.a
NAME_SRC = \
	cd.c \
	echo.c \
	pwd.c \
	env.c
NAME_OBJ=$(CMDS_SRC:.c=.o)

all: $(LIBFT) $(NAME)

clean:
	$(MAKE) clean -C ../libft
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -rf $(NAME)

re:	fclean all

cd: cd.o
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< $(LIBS)
pwd: pwd.o
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< $(LIBS)
env: env.o
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< $(LIBS)
echo: echo.o
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< $(LIBS)
export: export.o
	$(CC) $(CFLAGS) -o $@ $<

$(LIBFT):
	$(MAKE) -C ../libft

.PHONY: clear fclean re all
