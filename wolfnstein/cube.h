/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:21:52 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/25 13:20:19 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H
#define BUFFER_SIZE 1024
#define mx 2147483647
#define mn -2147483648

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>


typedef struct s_info {
	long long	floor[3];
	long long	ceiling[3];
	char		**map;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			x;
	int			y;
	char		headed;
}   t_info;

//parser
int parser(int ac, char **av, t_info *config);

//config
int config_check(t_info *config);

//utils
int has_cub(char *s);

//libc
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char 	*ft_substr(const char *s, unsigned int start, size_t len);
char 	*ft_strjoin(char *s1, const char *s2);
char *ft_strchr(const char *s, int c);
//getline
char	*get_next_line(int fd);

#endif