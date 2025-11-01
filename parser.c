/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:17 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/31 20:54:26 by sabadri          ###   ########.fr       */
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

void	parse_color(char *str, int color[3])
{
	int		i;
	char	*ptr;

	ptr = str;
	i = 0;
	while (*ptr && i < 3)
	{
		while (*ptr == ' ' || *ptr == ',')
			ptr++;
		color[i++] = ft_atoi(ptr);
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
	}
}

char	**add_map_line(char **map, char *line, int *count)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (*count + 2));
	if (!new_map)
		return (NULL);
	while (i < *count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[*count] = ft_strdup(line);
	new_map[*count + 1] = NULL;
	if (map)
		free(map);
	(*count)++;
	return (new_map);
}

void	init_struct(t_info *config)
{
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
}

static int	parse_line(char *line, t_info *config, int *k, int *p, int *mp_cnt)
{
	*p = 1;
	if (!ft_strncmp(line, "NO ", 3))
		config->north_path = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		config->south_path = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		config->west_path = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		config->east_path = ft_strdup(line + 3);
	else if (line[0] == 'F')
		parse_color(line + 2, config->floor);
	else if (line[0] == 'C')
		parse_color(line + 2, config->ceiling);
	else if (*k >= 6)
	{
		config->map = add_map_line(config->map, line, mp_cnt);
		*p = 0;
	}
	if (*p)
		(*k)++;
	return (0);
}

static int	read_cub_file(int fd, t_info *config)
{
	char	*line;
	int		k;
	int		p;
	int		map_count;

	k = 0;
	p = 0;
	map_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_line(line, config, &k, &p, &map_count);
		free(line);
	}
	return (0);
}

int	parser(int ac, char **av, t_info *config)
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
	read_cub_file(fd, config);
	close(fd);
	return (0);
}
