/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:08:37 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/22 18:59:10 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'D'
		|| c == 'W' || c == 'E' || c == 'S' || c == 'N');
}

static void	handle_player_pos(t_info *config, char c, int x, int y)
{
	config->headed = c;
	config->x = x;
	config->y = y;
}

int	all_chars(char **map, t_info *config)
{
	int	i;
	int	j;
	int	p;

	p = 0;
	i = 0;
	config->headed = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
				return (0);
			if (map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'N')
			{
				handle_player_pos(config, map[i][j], j, i);
				p++;
			}
			j++;
		}
		i++;
	}
	return (p == 1);
}
