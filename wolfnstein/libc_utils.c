/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 23:36:20 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/08 19:07:40 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char *ft_strchr(const char *s, int c)
{
    if (!s)
		return (NULL);
    while (*s)
    {
        if (*s == (char)c)
			return ((char *)s);
        s++;
    }
    if (c == '\0')
		return ((char *)s);
    return (NULL);
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    if (!s)
		return (NULL);
    size_t s_len = strlen(s);
    if (start >= s_len)
		return (ft_strdup(""));
    if (len > s_len - start)
		len = s_len - start;
    char *sub = malloc(len + 1);
    if (!sub)
		return (NULL);
    for (size_t i = 0; i < len; i++)
		sub[i] = s[start + i];
    sub[len] = '\0';
    return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
	
	i = 0;
    if (n == 0)
        return (0);
    while (i < n - 1 && s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(const char *s)
{
    int n = 0;
    int sign = 1;
    while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
    if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}

char *ft_strdup(const char *s)
{
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy)
		return (NULL);
    for (size_t i = 0; i < len; i++)
        copy[i] = s[i];
    copy[len] = '\0';
    return (copy);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

size_t ft_strlen(const char *s)
{
    size_t i;
    i = 0;
    while (s && *s)
	{
		s++;
        i++;
	}
    return (i);
}
char *ft_strjoin(char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *res = malloc(len1 + len2 + 1);
    if (!res) return NULL;
    size_t i = 0;
    for (; i < len1; i++) res[i] = s1[i];
    for (size_t j = 0; j < len2; j++) res[i + j] = s2[j];
    res[len1 + len2] = '\0';
    if (s1) free(s1);
    return res;
}