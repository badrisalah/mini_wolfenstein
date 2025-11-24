/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 02:37:01 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/21 19:15:16 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	parse_map_line(char *line, t_info *config, t_state *st, t_garbage **g)
{
	config->map = add_map_line(config->map, line, &st->map_cnt, g);
	return (0);
}
