/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:00:18 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/24 21:53:23 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_line(char *line, t_info *config, t_state *st, t_garbage **g)
{
	st->p = 1;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "DO", 2))
		&& (st->k >= 0 && st->k <= 4))
	{
		if (parse_texture_line(skipst(line), config, g))
			return (1);
		st->k++;
	}
	else if ((line[0] == 'F' || line[0] == 'C') && (st->k >= 5 && st->k <= 6))
	{
		if (parse_color_line(skipst(line), config))
			return (1);
		st->k++;
	}
	else if (st->k >= 7)
	{
		parse_map_line(line, config, st, g);
		st->p = 0;
	}
	return (0);
}

int	read_cub_file(int fd, t_info *config, t_garbage **g)
{
	char	*line;
	t_state	st;

	st.k = 0;
	st.p = 0;
	st.map_cnt = 0;
	line = get_next_line(fd, g);
	while (line != NULL)
	{
		if (parse_line(line, config, &st, g))
			return (1);
		line = get_next_line(fd, g);
	}
	return (0);
}
