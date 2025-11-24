/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:42:06 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/22 18:43:59 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	degres_to_rad(float angle)
{
	return (angle * (PI / 180));
}

int	int_to_hex(long arr[3])
{
	int	r;
	int	g;
	int	b;
	int	ans;

	b = arr[2];
	g = arr[1];
	r = arr[0];
	ans = (r << 16) | (g << 8) | b;
	return (ans);
}

int	cleanup_and_exit(t_game *cub)
{
	if (cub->mlx_ptr)
	{
		if (cub->img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->img.img);
		if (cub->tex_ea && cub->tex_ea->img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex_ea->img);
		if (cub->tex_no && cub->tex_no->img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex_no->img);
		if (cub->tex_so && cub->tex_so->img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex_so->img);
		if (cub->tex_we && cub->tex_we->img)
			mlx_destroy_image(cub->mlx_ptr, cub->tex_we->img);
		if (cub->door && cub->door->img)
			mlx_destroy_image(cub->mlx_ptr, cub->door->img);
		if (cub->overlay && cub->overlay->img)
			mlx_destroy_image(cub->mlx_ptr, cub->overlay->img);
		if (cub->mlx_win)
			mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	garbage_clear(cub->garb);
	exit(0);
}

void	get_map_dimensions(t_game *cub, int *width, int *height)
{
	int	x;
	int	y;
	int	max_width;

	*height = 0;
	max_width = 0;
	y = 0;
	while (cub->info->map[y])
	{
		x = 0;
		while (cub->info->map[y][x])
			x++;
		if (x > max_width)
			max_width = x;
		y++;
	}
	*width = max_width;
	*height = y;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
