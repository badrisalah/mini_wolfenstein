/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:17 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/25 13:21:48 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_line(char *line)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void parse_color(char *str, long long color[3])
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

char **add_map_line(char **map, char *line, int *count)
{
    char **new_map = malloc(sizeof(char *) * (*count + 2));
    if (!new_map) return NULL;

    for (int i = 0; i < *count; i++)
        new_map[i] = map[i];

    new_map[*count] = ft_strdup(line);
    new_map[*count + 1] = NULL;
    if (map)
        free(map);
    (*count)++;
    return new_map;
}

int parser(int ac, char **av, t_info *config)
{
    
	char	*line;
	int		fd;
	int		k;
	
	k = 0;
    if (ac < 2)
        return (printf("Error: need a .cub file\n"), 1);
    if (!has_cub(av[1]))
        return (printf("Error: file must end with .cub\n"), 1);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);
    int map_count = 0;
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
    while ((line = get_next_line(fd)) != NULL)
    {
		if (!ft_strncmp(line, "NO ", 3))
		{
			config->north_path = ft_strdup(line + 3);
			k++;
		}
        else if (!ft_strncmp(line, "SO ", 3))
		{
			config->south_path = ft_strdup(line + 3);
			k++;
		}
        else if (!ft_strncmp(line, "WE ", 3))
		{
			config->west_path = ft_strdup(line + 3);
			k++;
		}
        else if (!ft_strncmp(line, "EA ", 3))
		{
			config->east_path = ft_strdup(line + 3);
			k++;
		}
        else if (line[0] == 'F')
		{
			parse_color(line + 2, config->floor);
			k++;
		}
        else if (line[0] == 'C')
		{
			parse_color(line + 2, config->ceiling);
			k++;
		}
        else if (k >= 6)
			config->map = add_map_line(config->map, line, &map_count);
        free(line);
    }
    close(fd);
    return (0);
}
