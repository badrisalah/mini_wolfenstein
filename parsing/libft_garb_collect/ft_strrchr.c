/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:27:33 by sabadri          #+#    #+#             */
/*   Updated: 2025/05/04 13:20:00 by sabadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	tmp;
	size_t	i;

	i = ft_strlen(s);
	tmp = (char) c;
	if (s[i] == tmp)
		return ((char *) &s[i]);
	i--;
	while (i <= ft_strlen(s))
	{
		if (s[i] == tmp)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}
