/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:23:43 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/23 20:11:58 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_invalid_boundary(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
		return (1);
	if (j >= (int)ft_strlen(map[i - 1]) || is_outside(map, i - 1, j))
		return (1);
	if (j >= (int)ft_strlen(map[i + 1]) || is_outside(map, i + 1, j))
		return (1);
	if (is_outside(map, i, j - 1) || is_outside(map, i, j + 1))
		return (1);
	return (0);
}

int	is_line_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	has_map_content(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '1' || s[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

int	is_outside(char **map, int i, int j)
{
	if (map[i][j] == ' ' || map[i][j] == '\t')
		return (1);
	return (0);
}
