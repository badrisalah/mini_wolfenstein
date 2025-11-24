/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:20:47 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/24 21:53:39 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	map_checker(t_info *config)
{
	int	i;
	int	in_map;
	int	j;

	in_map = 0;
	i = 0;
	while (config->map[i] && is_line_empty(config->map[i]))
		i++;
	while (config->map[i])
	{
		if (has_map_content(config->map[i]))
			in_map = 1;
		else if (in_map && is_line_empty(config->map[i]))
		{
			j = i + 1;
			while (config->map[j] && is_line_empty(config->map[j]))
				j++;
			if (config->map[j] && has_map_content(config->map[j]))
				return (printf("Error\nempty line inside map\n"), 1);
			break ;
		}
		i++;
	}
	return (0);
}

static int	validate_map_tiles(char **map, int *last_num_cols)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]) && is_invalid_boundary(map, i, j))
			{
				printf("Error\nmap not closed\n");
				return (1);
			}
			j++;
			if (*last_num_cols < j)
				*last_num_cols = j;
		}
		i++;
	}
	return (0);
}

int	check_boundaries(t_info *config)
{
	int		last_num_cols;

	last_num_cols = 0;
	if (validate_map_tiles(config->map, &last_num_cols))
		return (1);
	config->rows = 0;
	while (config->map[config->rows])
		config->rows++;
	config->cols = last_num_cols;
	return (0);
}
