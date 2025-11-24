/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:54:30 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/24 21:54:51 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	parse_color(char *str, long color[3])
{
	int	i;

	i = 0;
	while (*str)
	{
		if (i >= 3)
			return (1);
		if (!ft_isdigit(*str))
			return (1);
		color[i] = ft_atoi(str);
		if (color[i] < 0 || color[i] > 255)
			return (1);
		while (ft_isdigit(*str))
			str++;
		if (i < 2)
		{
			if (*str != ',')
				return (1);
			str++;
		}
		i++;
	}
	return (i != 3);
}

int	parse_color_line(char *line, t_info *config)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (config->check[5])
			return (1);
		if (parse_color(line + 2, config->floor))
			return (1);
		config->check[5] = true;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (config->check[6])
			return (1);
		if (parse_color(line + 2, config->ceiling))
			return (1);
		config->check[6] = true;
	}
	else
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
