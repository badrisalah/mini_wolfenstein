/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:29:50 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/16 22:35:09 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void load_overlay(t_game *cub, char *path)
{
    cub->overlay = malloc(sizeof(t_texture));
    cub->overlay->img = mlx_xpm_file_to_image(
        cub->mlx_ptr, path, &cub->overlay->width, &cub->overlay->height);
    cub->overlay->addr = mlx_get_data_addr(
        cub->overlay->img,
        &cub->overlay->bits_per_pixel,
        &cub->overlay->line_length,
        &cub->overlay->endian);
    cub->overlay->texture_path = path;
}

void update_and_draw_overlay(t_game *cub, float current_time)
{
    int base_y = 30;
    int y_offset = base_y + (int)(6 * sin(current_time));
    draw_overlay(cub, 0, y_offset + 400);
}

void draw_overlay(t_game *cub, int x_offset, int y_offset)
{
    t_texture *ov = cub->overlay;

    for (int y = 0; y < ov->height; y++)
    {
        for (int x = 0; x < ov->width; x++)
        {
            int offset = y * ov->line_length + x * (ov->bits_per_pixel / 8);
            unsigned int color = *(unsigned int *)(ov->addr + offset);

            if ((color & 0xFF000000) == 0xFF000000)
                continue;

            put_pixel(&cub->img,
                x + x_offset,
                y + y_offset,
                color);
        }
    }
}


