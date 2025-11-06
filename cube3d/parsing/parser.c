/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:17 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/05 05:50:13 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	parse_color(char *str, int color[3])
{
	int		i;
	char	*ptr;

	ptr = str;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == ',')
			ptr++;
		if (i >= 3)
			return (1);
		color[i++] = ft_atoi(ptr);
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
	}
	return (0);
}

char	**add_map_line(char **map, char *line, int *count, t_garbage **garb)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_malloc(sizeof(char *) * (*count + 2), garb);
	if (!new_map)
		return (NULL);
	while (i < *count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[*count] = ft_strdup_g(line, garb);
	new_map[*count + 1] = NULL;
	(*count)++;
	return (new_map);
}


void	init_struct(t_info *config)
{
	int	i;

	i = 7;
	config->map = NULL;
	config->north_path = NULL;
	config->south_path = NULL;
	config->west_path = NULL;
	config->east_path = NULL;
	config->ceiling[0] = 1e9;
	config->floor[0] = 1e9;
	config->headed = '0';
	config->x = 0;
	config->y = 0;
	while (i--)
		config->check[i] = false;
}

char	*skipst(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s + i);
}

int	parse_line(char *line, t_info *config, int *k, int *p, int *mp_cnt, t_garbage **g)
{
	line = skipst(line);
	*p = 1;
	if (!ft_strncmp(line, "NO", 2))
	{
		if (config->check[0] == true)
			return (1);
		config->north_path = ft_strdup_g(skipst(line + 2), g);
		config->check[0] = true;
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (config->check[1] == true)
			return (1);
		config->south_path = ft_strdup_g(skipst(line + 2), g);
		config->check[1] = true;
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (config->check[2] == true)
			return (1);
		config->west_path = ft_strdup_g(skipst(line + 2), g);
		config->check[2] = true;
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (config->check[3] == true)
			return (1);
		config->east_path = ft_strdup_g(skipst(line + 2), g);
		config->check[3] = true;
	}
	else if (line[0] == 'F')
	{
		if (config->check[4] == true)
			return (1);
		if (parse_color(skipst(line + 1), config->floor))
			return (1);
		config->check[4] = true;
	}
	else if (line[0] == 'C')
	{	if (config->check[5] == true)
			return (1);
		if (parse_color(skipst(line + 1), config->ceiling))
			return (1);
		config->check[5] = true;
	}
	else if (*k >= 6)
	{
		config->map = add_map_line(config->map, line, mp_cnt, g);
		*p = 0;
	}
	if (*p)
		(*k)++;
	return (0);
}

static int	read_cub_file(int fd, t_info *config, t_garbage **g)
{
	char	*line;
	int		k;
	int		p;
	int		map_count;

	k = 0;
	p = 0;
	map_count = 0;
	while ((line = get_next_line(fd, g)) != NULL)
	{
		if (parse_line(line, config, &k, &p, &map_count, g))
			return (1);
	}
	return (0);
}

int	parser(int ac, char **av, t_info *config, t_garbage **g)
{
	int	fd;

	if (ac < 2)
		return (printf("Error\nneed a .cub file\n"), 1);
	if (!has_cub(av[1]))
		return (printf("Error\nfile must end with .cub\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	init_struct(config);
	if (read_cub_file(fd, config, g))
		return (1);
	close(fd);
	return (0);
}
