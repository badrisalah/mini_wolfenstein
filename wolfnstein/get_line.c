/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:28:31 by sabadri           #+#    #+#             */
/*   Updated: 2025/10/07 22:48:55 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char *fill_line_buffer(int fd, char *line, char *buffer)
{
    ssize_t b_read;

    while ((b_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[b_read] = '\0';
        if (!line)
            line = ft_strdup(buffer);
        else
            line = ft_strjoin(line, buffer);

        if (ft_strchr(buffer, '\n'))
            break;
    }

    if (b_read < 0)
    {
        if (line)
			free(line);
        return NULL;
    }

    return line;
}

static char *extract_line(char *line_buffer)
{
    int i = 0;
    if (!line_buffer)
        return NULL;
    while (line_buffer[i] && line_buffer[i] != '\n')
        i++;
    return ft_substr(line_buffer, 0, i);
}

static char *set_remainder(char *line_buffer)
{
    size_t i = 0;
    char *remainder;

    if (!line_buffer) return NULL;
    while (line_buffer[i] && line_buffer[i] != '\n')
        i++;
    if (!line_buffer[i])
    {
        free(line_buffer);
        return NULL;
    }
    remainder = ft_substr(line_buffer, i + 1, strlen(line_buffer) - i - 1);
    free(line_buffer);
    return remainder;
}

char *get_next_line(int fd)
{
    static char *line_buffer;
    char *str;
    char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer) return NULL;

    line_buffer = fill_line_buffer(fd, line_buffer, buffer);
    free(buffer);
    if (!line_buffer) return NULL;

    str = extract_line(line_buffer);
    line_buffer = set_remainder(line_buffer);
    return str;
}