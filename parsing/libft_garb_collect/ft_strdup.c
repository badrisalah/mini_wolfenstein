/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:20:04 by sabadri          #+#    #+#             */
/*   Updated: 2025/05/24 22:01:42 by sabadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//normal ft_strdup() func.
char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	cpy = (char *) malloc(sizeof(char) * len);
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s1, len);
	return (cpy);
}
