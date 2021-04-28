CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libq.a
SRCS = \
	enq.c \
	deq.c\
	front.c\
	q_empty.c\
	q_size.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.PHONY: all clean fclean re .c.o
