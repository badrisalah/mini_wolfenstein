/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:16:09 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/21 19:16:19 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_struct(t_info *config)
{
	int	i;

	i = 7;
	config->map = NULL;
	config->door = NULL;
	config->north_path = NULL;
	config->south_path = NULL;
	config->west_path = NULL;
	config->east_path = NULL;
	config->ceiling[0] = 1e9;
	config->floor[0] = 1e9;
	config->headed = '0';
	config->x = 0;
	config->y = 0;
	while (i--)
		config->check[i] = false;
}
