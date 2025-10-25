/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:23:35 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/25 11:11:34 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	t_info	config;

	if (ac != 2)
		return (printf("need 2 args !\n"), 1);
	if (parser(ac, av, &config))
		return (printf("ERROR: input isnt compatible !\n"), 1);
	if (config_check(&config))
		return (1);
	return (0);
}
