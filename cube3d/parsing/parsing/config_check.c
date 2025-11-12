/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:55:46 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/12 18:08:04 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	config_check(t_info *config)
{
	if (!config)
		return (1);
	if (!config->north_path || !config->south_path
		|| !config->west_path || !config->east_path)
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
