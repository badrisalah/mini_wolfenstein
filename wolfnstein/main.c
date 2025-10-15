/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:23:35 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/10 21:29:55 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int ac,char **av)
{
	t_info config;

	if (ac != 2)
		return (printf("need 2 args !\n"), 1);
	if (parser(ac, av, &config))
		return (printf("ERROR: input isnt compatible !\n"), 1);
	if (config_check(&config))
		return (1);
	
	return (0);
	}
	// printf("north -> [%s]\n",config.north_path);
	// printf("south -> [%s]\n",config.south_path);
	// printf("east -> [%s]\n",config.east_path);
	// printf("west -> [%s]\n",config.west_path);
	// printf("[%d] [%d] [%d] \n", config.floor[0],config.floor[1], config.floor[2]);
	// printf("[%d] [%d] [%d] \n", config.ceiling[0],config.ceiling[1], config.ceiling[2]);
	// for (int i = 0; config.map[i]; i++)
	// 	printf("%s\n", config.map[i]);