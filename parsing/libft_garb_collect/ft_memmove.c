/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:07:14 by sabadri          #+#    #+#             */
/*   Updated: 2025/05/04 13:19:15 by sabadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tsrc;
	unsigned char	*tdst;

	tsrc = (unsigned char *) src;
	tdst = (unsigned char *) dst;
	if (tdst > tsrc)
	{
		while (len > 0)
		{
			len--;
			tdst[len] = tsrc[len];
		}
	}
	else if (tdst < tsrc)
	{
		ft_memcpy(dst, src, len);
	}
	return (tdst);
}
