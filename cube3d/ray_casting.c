/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:31:36 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/06 01:17:44 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void    cast_ray(float ray_angle, int strip_id, t_game *cub, t_ray *rays)
{
    // float x_intercept;
    // float y_intercept;
    t_intercept intercept;
    t_hori *hori;
    t_vert *vert;
    t_step *steps;
    steps = malloc(sizeof(t_step));
    identifing_ray_facing(ray_angle, strip_id, rays);
    for_horizontal_intersection(&intercept, rays, strip_id, cub);
    horizontal_steps(steps, rays, strip_id);
    hori = horizontal_part(intercept, *steps, cub, strip_id);
    for_vertical_intersection(&intercept, rays, strip_id, cub);
    vertical_steps(steps, rays, strip_id);
    vert = vertical_part(intercept, *steps, cub, strip_id);
    smallest_distance_adaptation(*hori, *vert, rays, strip_id);
    free(steps);
    free(hori);
    free(vert);
}
void    cast_all_rays(t_game *cub)
{
    float    ray_angle;
    int        strip_id;
    strip_id = 0;
    ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
    while (strip_id < NUM_RAYS)
    {
        ray_angle = normalize_angle(ray_angle);
        cast_ray(ray_angle, strip_id, cub, cub->rays);
        ray_angle += FOV_ANGLE / NUM_RAYS;
        strip_id++;
    }
}

int int_to_hex(int arr[3])
{
    int r;
    int g;
    int b;
	int ans;

	b = arr[2];
	g = arr[1];
	r = arr[0];
    ans = (r << 16) | (g << 8) | b;
    return (ans);
}

void draw_wall_with_ceiling_floor(t_game *cub, int strip_id, float wall_height)
{
    int start_x;
    int end_x;
    float wall_top;
    int  wall_bottom;
    int y;
	t_texture *text;

	start_x = strip_id;
	end_x = (strip_id + 1);
    
	if (start_x >= WIDTH)
	    return;
	if (end_x > WIDTH)
	    end_x = WIDTH;
    wall_top = (HEIGHT / 2.0f) - (floor(wall_height) / 2.0f);
    wall_bottom = (HEIGHT / 2) + (floor(wall_height) / 2);
    if (cub->rays[strip_id].was_hit_vertical)
    {
        if (cub->rays[strip_id].is_ray_facing_right)
            text = cub->tex_ea;
        else
            text = cub->tex_we;
    }
    else
    {
        if (cub->rays[strip_id].is_ray_facing_down)
            text = cub->tex_so;
        else
            text = cub->tex_no;
    }
    while (start_x < end_x)
    {
        y = 0;
        while (y < (int)wall_top)
        {
            put_pixel(&cub->img, start_x, y, int_to_hex(cub->game_info->ceiling));  // Sky blue
            y++;
        }
        while (y < wall_bottom)
        {
            // put_texture(cub, text, strip_id, wall_height, wall_top);
            // put_pixel(&cub->img, start_x, y, 0xFFFFFFF);
            put_texture_preloaded(cub, text, strip_id, start_x, y, wall_height, wall_top);
            y++;
        }
        while (y < HEIGHT)
        {
            put_pixel(&cub->img, start_x, y, int_to_hex(cub->game_info->floor));  // Forest green
            y++;
        }
        start_x++;
    }
}
void    render_the_rays(t_game *cub)
{
    int        i;
    float    wall_height;
    float    corrected_distance;
    i = 0;
    cast_all_rays(cub);
    while (i < NUM_RAYS)
    {
        corrected_distance = cub->rays[i].distance 
                * cos(cub->rays[i].ray_angle - cub->player->rotation_angle);
        wall_height = (TILE_SIZE * HEIGHT) / corrected_distance;
        draw_wall_with_ceiling_floor(cub, i, wall_height);
        i++;
    }
}