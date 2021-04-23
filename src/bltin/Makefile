CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -shared -fPIC
NAME		= libcmds.so
NAME_SRC	=\
			echo.c \
			cd.c \
			pwd.c \
			export.c \
			unset.c\
			exit.c
NAME_OBJ	= $(NAME_SRC:.c=.o)


all: $(NAME)

clean:
	$(MAKE) clean -C ../libft
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -rf $(NAME)

re:	fclean all


$(NAME): $(NAME_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clear fclean re all
