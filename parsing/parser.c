/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:17 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/24 21:53:10 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	parser(int ac, char **av, t_info *config, t_garbage **g)
{
	int	fd;

	if (ac < 2)
		return (printf("Error\nneed a .cub file\n"), 1);
	if (!has_cub(av[1]))
		return (printf("Error\nfile must end with .cub\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	init_struct(config);
	if (read_cub_file(fd, config, g))
		return (close(fd), 1);
	close(fd);
	return (0);
}
