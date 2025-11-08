/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:00:18 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/08 17:23:00 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_texture_line(char *line, t_info *config, t_garbage **g)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (config->check[0])
			return (1);
		config->north_path = ft_strdup_g(skipst(line + 2), g);
		config->check[0] = true;
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (config->check[1])
			return (1);
		config->south_path = ft_strdup_g(skipst(line + 2), g);
		config->check[1] = true;
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (config->check[2])
			return (1);
		config->west_path = ft_strdup_g(skipst(line + 2), g);
		config->check[2] = true;
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (config->check[3])
			return (1);
		config->east_path = ft_strdup_g(skipst(line + 2), g);
		config->check[3] = true;
	}
	else
		return (1);
	return (0);
}

static int	parse_color_line(char *line, t_info *config)
{
	if (line[0] == 'F')
	{
		if (config->check[4])
			return (1);
		if (parse_color(skipst(line + 1), config->floor))
			return (1);
		config->check[4] = true;
	}
	else if (line[0] == 'C')
	{
		if (config->check[5])
			return (1);
		if (parse_color(skipst(line + 1), config->ceiling))
			return (1);
		config->check[5] = true;
	}
	else
		return (1);
	return (0);
}

static int	parse_line(char *line, t_info *config, t_state *st, t_garbage **g)
{
	line = skipst(line);
	st->p = 1;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (parse_texture_line(line, config, g))
			return (1);
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		if (parse_color_line(line, config))
			return (1);
	}
	else if (st->k >= 6)
	{
		parse_map_line(line, config, st, g);
		st->p = 0;
	}
	if (st->p)
		st->k++;
	return (0);
}

int	read_cub_file(int fd, t_info *config, t_garbage **g)
{
	char	*line;
	t_state	st;

	st.k = 0;
	st.p = 0;
	st.map_cnt = 0;
	while ((line = get_next_line(fd, g)) != NULL)
	{
		if (parse_line(line, config, &st, g))
			return (1);
	}
	return (0);
}
