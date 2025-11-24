/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:55:27 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/24 21:56:10 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	player_check(char **map)
{
	int	i;
	int	j;
	int	ans;

	ans = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				ans++;
			j++;
		}
		i++;
	}
	return (ans != 1);
}

int	door_check(char **map)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	f = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if ((map[i][j - 1] == '1' && map[i][j + 1] == '1'))
					f++;
				if ((map[i - 1][j] == '1' && map[i + 1][j] == '1'))
					f++;
			}
			j++;
		}
		i++;
	}
	return (f == 1);
}

int	config_check(t_info *config)
{
	if (!config)
		return (1);
	if (!config->north_path || !config->south_path
		|| !config->west_path || !config->east_path || !config->door)
		return (printf("Error\nmissing texture path\n"), 1);
	if (floor_ceiling_check(config))
		return (printf("Error\nfloor/ceiling [x] should be n->[0,255]\n"), 1);
	if (!config->map || !config->map[0])
		return (printf("Error\nmissing map data\n"), 1);
	if (map_checker(config))
		return (printf("Error\nmap error\n"), 1);
	if (player_check(config->map))
		return (printf("Error\nno/multiple players\n"), 1);
	if (check_boundaries(config))
		return (printf("Error\nboundaries error\n"), 1);
	if (!door_check(config->map))
		return (printf("Error\n Door should be surrounded with 1"), 1);
	if (!all_chars(config->map, config))
	{
		printf("Error\nno valid characters\n");
		return (1);
	}
	return (0);
}
