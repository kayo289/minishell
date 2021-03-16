CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= libcmds.so
NAME_SRC	= cd.c 
NAME_OBJ	= $(NAME_SRC:.c=.o)


all: $(NAME)

clean:
	$(MAKE) clean -C ../libft
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -rf $(NAME)

re:	fclean all


VAL	= $(eval export LD_LIBRARY_PATH=${PWD})
$(NAME): $(NAME_OBJ)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^
	export LD_LIBRARY_PATH=${PWD}

.PHONY: clear fclean re all
