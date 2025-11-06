/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:21:52 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/05 05:37:21 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft_garb_collect/libft.h"

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


typedef struct s_info {
	int			floor[3];
	int			ceiling[3];
	bool		check[7];
	char		**map;
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
int		parser(int ac, char **av, t_info *config, t_garbage **g);

//config
int		config_check(t_info *config);

//utils
int		has_cub(char *s);

char	*get_next_line(int fd, t_garbage **g);

#endif