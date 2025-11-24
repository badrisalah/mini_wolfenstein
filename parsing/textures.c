/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:04:41 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/21 19:42:07 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_texture_i(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (0);
	else if (!ft_strncmp(line, "SO", 2))
		return (1);
	else if (!ft_strncmp(line, "WE", 2))
		return (2);
	else if (!ft_strncmp(line, "EA", 2))
		return (3);
	else if (!ft_strncmp(line, "DO", 2))
		return (4);
	return (-1);
}

void	set_texture_path(t_info *config, int i, char *path)
{
	if (i == 0)
		config->north_path = path;
	else if (i == 1)
		config->south_path = path;
	else if (i == 2)
		config->west_path = path;
	else if (i == 3)
		config->east_path = path;
	else if (i == 4)
		config->door = path;
}

char	*texture(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == ' ')
		i--;
	line[i + 1] = '\0';
	return (line);
}

int	parse_texture_line(char *line, t_info *config, t_garbage **g)
{
	int		i;
	char	*path;

	i = get_texture_i(line);
	if (i == -1 || config->check[i])
		return (1);
	line = skipst(line + 2);
	path = ft_strdup_g(texture(line), g);
	if (!path)
		return (1);
	set_texture_path(config, i, path);
	config->check[i] = true;
	return (0);
}
