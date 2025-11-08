/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:55:46 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/08 17:24:07 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	mark_trailing_empty_lines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (i >= 0)
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t' ||  map[i][j] == '\n'))
			j++;
		if (map[i][j] == '\0')
		{
			map[i][0] = 'Z';
			map[i][1] = '\0';
		}
		else
			break ;
		i--;
	}
}

int	check_boundaries(t_info *config)
{
	char	**map;
	int		i;
	int		j;

	map = config->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
			{
				if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1]
					|| is_outside(map, i - 1, j) || is_outside(map, i + 1, j)
					|| is_outside(map, i, j - 1)
					|| is_outside(map, i, j + 1))
				{
					printf("Error\nmap not closed\n");
					return (1);
				}
			}
			j++;   
        }
        i++;
    }
    config->num_rows = 15;
    config->num_cols = 20;
	return (0);
}

int	validate_map(t_info *config)
{
	if (map_checker(config))
		return (1);
	mark_trailing_empty_lines(config->map);
	if (check_boundaries(config))
		return (1);
	return (0);
}

bool	floor_ceiling_check(t_info *config)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (config->ceiling[i] == (int)1e9
			|| config->ceiling[i] < 0
			|| config->ceiling[i] > 255)
			return (true);
		if (config->floor[i] == (int)1e9
			|| config->floor[i] < 0
			|| config->floor[i] > 255)
			return (true);
		i++;
	}
	return (false);
}

void	free_paths(char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (paths[i])
			free(paths[i]);
		i++;
	}
	free(paths);
}

// bool	files_check(t_info *config)
// {
// 	char	**paths;
// 	int		idx;
// 	int		fd;

// 	paths = malloc(sizeof(char *) * 5);
// 	idx = 0;
// 	paths[0] = ft_strdup(config->east_path);
// 	paths[1] = ft_strdup(config->north_path);
// 	paths[2] = ft_strdup(config->west_path);
// 	paths[3] = ft_strdup(config->south_path);
// 	paths[4] = NULL;
// 	while (idx < 4)
// 	{
// 		fd = open(paths[idx], O_RDONLY);
// 		if (fd < 0)
// 		{
// 			printf("Error\n in file %s\n", paths[idx]);
// 			return (free_paths(paths, idx), false);
// 		}
// 		close(fd);
// 		idx++;
// 	}
// 	free_paths(paths, idx);
// 	return (true);
// }

int	all_chars(char **map, t_info *config)
{
	int	i;
	int	j;
	int	direction;

	direction = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != '1'
				&& map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != 'S'
				&& map[i][j] != 'N')
				return (1);
			if (map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'N')
			{
				config->headed = map[i][j];
				config->x = j;
				config->y = i;
				direction++;
			}
			j++;
		}
		i++;
	}
	return (direction != 1);
}

int	config_check(t_info *config)
{
	if (!config)
		return (1);
	if (!config->north_path || !config->south_path
		|| !config->west_path || !config->east_path)// || !files_check(config)
		return (printf("Error\nmissing texture path\n"), 1);
	if (floor_ceiling_check(config))
		return (printf("Error\nfloor/ceiling [x] should be n->[0,255]\n"), 1);
	if (!config->map || !config->map[0])
		return (printf("Error\nmissing map data\n"), 1);
	if (map_checker(config))
		return (printf("Error\nmap error\n"), 1);
	if (check_boundaries(config))
		return (printf("Error\nboundaries error\n"), 1);
	if (!all_chars(config->map, config))
	{
		printf("Error\nno valid characters");
		return (1);
	}
	return (0);
}
