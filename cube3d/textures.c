/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:55:43 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/31 17:35:28 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *which_texture(t_game cub, t_ray *rays, int strip_id)
{
    // Check if vertical or horizontal wall hit
    if (rays[strip_id].was_hit_vertical)
    {
        // Vertical wall - check left/right
        if (rays[strip_id].is_ray_facing_right)
            return (cub.game_info->west_path);  // Hit west-facing wall
        else
            return (cub.game_info->east_path);  // Hit east-facing wall
    }
    else
    {
        // Horizontal wall - check up/down
        if (rays[strip_id].is_ray_facing_down)
            return (cub.game_info->north_path);  // Hit north-facing wall
        else
            return (cub.game_info->south_path);  // Hit south-facing wall
    }
}

void   load_texture(t_game *cub, t_texture *texture, char *text_path)
{
    texture->img = mlx_xpm_file_to_image(cub->mlx_ptr, text_path, 
            &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error: Failed to load texture: %s\n", text_path);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
        &texture->line_length, &texture->endian);
}

// Helper function to get color from texture
int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char *pixel;
    
    // Safety bounds check
    if (tex_x < 0 || tex_x >= texture->width || 
        tex_y < 0 || tex_y >= texture->height)
        return (0x000000);
    
    // CORRECT formula: pixel = addr + (y * line_length) + (x * bytes_per_pixel)
    pixel = texture->addr + (tex_y * texture->line_length + 
                             tex_x * (texture->bits_per_pixel / 8));
    
    return (*(int *)pixel);
}
void put_texture_preloaded(t_game *cub, t_texture *texture, int strip_id, int screen_x, int screen_y, float wall_height, float wall_top)
{
    int     tex_x;
    int     tex_y;
    float   wall_x;
    float   wall_progress;
    int     color;

    // Calculate texture X
    if (cub->rays[strip_id].was_hit_vertical)
        wall_x = cub->rays[strip_id].wall_hit_y;
    else
        wall_x = cub->rays[strip_id].wall_hit_x;
    
    wall_x = fmod(wall_x, TILE_SIZE) / TILE_SIZE;
    tex_x = (int)(wall_x * texture->width);
    
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    
    // Calculate texture Y using floating point precision
    wall_progress = ((float)screen_y - wall_top) / wall_height;
    
    // Clamp progress
    if (wall_progress < 0.0f)
        wall_progress = 0.0f;
    if (wall_progress > 1.0f)
        wall_progress = 1.0f;
    
    // Map to texture coordinate
    tex_y = (int)(wall_progress * (float)texture->height);
    
    // Safety bounds
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= texture->height)
        tex_y = texture->height - 1;
    
    // Get and draw color
    color = get_texture_color(texture, tex_x, tex_y);
    put_pixel(&cub->img, screen_x, screen_y, color);
}