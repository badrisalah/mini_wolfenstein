CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cube

SRCS = main.c config_check.c get_line.c parser.c utils.c \
       libft_garb_collect/ft_atoi.c \
       libft_garb_collect/ft_strdup_g.c \
       libft_garb_collect/ft_strjoin_g.c \
       libft_garb_collect/ft_substr_g.c \
       libft_garb_collect/garb_coll_init.c \
       libft_garb_collect/garb_coll_clear.c \
       libft_garb_collect/ft_strlen.c \
       libft_garb_collect/ft_strcmp.c \
       libft_garb_collect/ft_strncmp.c \
       libft_garb_collect/ft_strchr.c \
       libft_garb_collect/ft_memcpy.c \
       libft_garb_collect/ft_bzero.c

HEADERS = cube.h libft_garb_collect/libft.h

OBJS = $(SRCS:.c=.o)
INCLUDES = -Ilibft_garb_collect

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
