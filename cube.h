/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:21:52 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/31 20:52:21 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define BUFFER_SIZE 1024
# define MX 2147483647
# define MN -2147483648
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <stdbool.h>


// typedef struct s_img
// {
//     void    *img;         // Image pointer
//     char    *addr;        // Direct access to pixel data
//     int        bits_per_pixel;
//     int        line_length;
//     int        endian;
// }    t_img; 

// typedef struct s_player
// {
//     float   x;
//     float   y;
//     float   rotation_angle;
//     float   move_speed;
//     float   turn_speed;
//     float   turn_direction;
//     float   walk_direction;
// }   t_player;

// typedef struct s_ray
// {
//     float    ray_angle;
//     float    wall_hit_x;
//     float    wall_hit_y;
//     float   distance;
//     bool     was_hit_vertical;
//     bool     was_hit_horizontal;
//     bool     is_ray_facing_up;
//     bool     is_ray_facing_down;
//     bool     is_ray_facing_left;
//     bool     is_ray_facing_right;
//     int        wall_hit_content;
// }   t_ray;
// typedef struct  s_game
// {
//     void    *mlx_ptr;
//     void    *mlx_win;
//     char    **map;
//     float   x_map;
//     float   y_map;
//     t_img   img;
//     t_player *player;
//     t_ray    rays[NUM_RAYS];
// }   t_game;

typedef struct s_info {
	int			floor[3]; // should be conveted to hex then passed in an int variable
	int			ceiling[3];
	// char		*ceiling;
	//  should be conveted to hex then passed in an int variable
	char		**map; //should add the num of cols and rows 
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	float		x;
	float		y;
	int			num_rows;
	int			num_cols;
	char		headed;
}   t_info;

//parser
int		parser(int ac, char **av, t_info *config);

//config
int		config_check(t_info *config);

//utils
int		has_cub(char *s);

//libc
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char 	*ft_substr(const char *s, unsigned int start, size_t len);
char 	*ft_strjoin(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
//getline
char	*get_next_line(int fd);

#endif