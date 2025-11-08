SRCS = main.c tools.c events.c player.c draw_the_map.c ray_casting.c ray_casting_tools.c \
	horizontal_part_tools.c vertical_part_tools.c parsing/config_check.c parsing/get_line.c \
	parsing/libc_utils.c parsing/parser.c parsing/utils.c textures.c parsing/libft_garb_collect/ft_atoi.c \
    parsing/utils2.c parsing/libft_garb_collect/ft_strdup_g.c \
       parsing/libft_garb_collect/ft_strjoin_g.c \
       parsing/libft_garb_collect/ft_substr_g.c \
       parsing/libft_garb_collect/garb_coll_init.c \
       parsing/libft_garb_collect/garb_coll_clear.c \
       parsing/libft_garb_collect/ft_strlen.c \
       parsing/libft_garb_collect/ft_strcmp.c \
       parsing/libft_garb_collect/ft_strncmp.c \
       parsing/libft_garb_collect/ft_strchr.c \
       parsing/libft_garb_collect/ft_memcpy.c \
       parsing/libft_garb_collect/ft_bzero.c
MLX_DIR = ./minilibx-linux
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/usr/include -I$(MLX_DIR) -O3
# CFLAGS = -I/usr/include -I$(MLX_DIR) -O3 
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3D

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@echo "Building MinilibX..."
	@cd $(MLX_DIR) && make -f Makefile all 2>/dev/null || \
	(cp Makefile.mk Makefile.gen && \
	 sed -i 's/%%%%/./' Makefile.gen && \
	 make -f Makefile.gen all)

$(NAME): $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) -fsanitize=address $(OBJS) $(LDFLAGS) -o $(NAME)
	make -C ./parsing all

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ./parsing clean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	make -C ./parsing fclean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

re: fclean all
	make -C ./parsing re

