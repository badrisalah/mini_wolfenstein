/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:15:18 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/23 20:08:57 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*skipst(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s + i);
}

int	has_cub(char *s)
{
	size_t	ss;

	ss = ft_strlen(s);
	if (ss < 4)
		return (0);
	if (!ft_strcmp(".cub", s + ss - 4))
		return (1);
	return (0);
}
