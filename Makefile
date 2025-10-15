CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c config_check.c get_line.c libc_utils.c parser.c utils.c
HEADERS = cube.h
NAME = cube
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

