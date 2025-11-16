/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:05:16 by monabati          #+#    #+#             */
/*   Updated: 2025/11/16 20:05:28 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace1(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

static int	ft_cheker(int c)
{
	if (c < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	long	overflow;
	int		sign;

	i = ft_isspace1(str);
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow = result;
		result *= 10;
		result += str[i++] - 48;
		if (result / 10 != overflow)
			return (ft_cheker(sign));
	}
	if (!i)
		return (-1);
	return (result * sign);
}
