/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:29:50 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/28 18:50:18 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_and_draw_overlay(t_game *cub, float current_time)
{
	int	base_y;
	int	y_offset;

	base_y = 30;
	y_offset = base_y + (int)(6 * sin(current_time));
	draw_overlay(cub, 0, y_offset + 400);
}

void	draw_overlay(t_game *cub, int x_offset, int y_offset)
{
	t_texture		*ov;
	int				y;
	int				x;
	int				offset;
	unsigned int	color;

	ov = cub->overlay;
	y = 0;
	while (y < ov->height)
	{
		x = 0;
		while (x < ov->width)
		{
			offset = y * ov->line_length + x * (ov->bits_per_pixel / 8);
			color = *(unsigned int *)(ov->addr + offset);
			if ((color & 0xFF000000) == 0xFF000000)
			{
				x++;
				continue ;
			}
			put_pixel(&cub->img, x + x_offset, y + y_offset, color);
			x++;
		}
		y++;
	}
}
