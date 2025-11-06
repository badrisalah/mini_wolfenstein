#include "cub3d.h"

#define MINIMAP_VIEW 10  // 10x10 tiles around the player
#define MINIMAP_SIZE 200 // fixed minimap size in pixels

void get_map_dimensions(t_game *cub, int *width, int *height)
{
    int x, y, max_width;

    *height = 0;
    max_width = 0;
    y = 0;
    while (cub->game_info->map[y])
    {
        x = 0;
        while (cub->game_info->map[y][x])
            x++;
        if (x > max_width)
            max_width = x;
        y++;
    }
    *width = max_width;
    *height = y;
}

void draw_tile(t_game *cub, int start_x, int start_y, int tile_size, int color)
{
    for (int y = start_y; y < start_y + tile_size; y++)
        for (int x = start_x; x < start_x + tile_size; x++)
            put_pixel(&cub->img, x, y, color);
}

void draw_player_on_minimap(t_game *cub, int tile_size)
{
    int center_x = MINIMAP_SIZE / 2;
    int center_y = MINIMAP_SIZE / 2;
    int size = tile_size;

    if (size < 3) size = 3;
    if (size > 15) size = 15;

    for (int y = center_y - size / 2; y <= center_y + size / 2; y++)
        for (int x = center_x - size / 2; x <= center_x + size / 2; x++)
            put_pixel(&cub->img, x, y, 0xFF0000);
}

void draw_minimap(t_game *cub)
{
    int map_width, map_height;
    get_map_dimensions(cub, &map_width, &map_height);

    // tile_size calculated so that the minimap fits in MINIMAP_SIZE
    int tile_size = MINIMAP_SIZE / MINIMAP_VIEW;

    int player_tile_x = (int)(cub->player->x / TILE_SIZE);
    int player_tile_y = (int)(cub->player->y / TILE_SIZE);

    int view_radius = MINIMAP_VIEW / 2;
    int start_x = player_tile_x - view_radius;
    int start_y = player_tile_y - view_radius;
    for (int y = 0; y < MINIMAP_VIEW; y++)
    {
        for (int x = 0; x < MINIMAP_VIEW; x++)
        {
            int map_x = start_x + x;
            int map_y = start_y + y;
            int color = 0x444444;

            if (map_x >= 0 && map_y >= 0 && map_x < map_width && map_y < map_height)
            {
                char tile = cub->game_info->map[map_y][map_x];
                if (tile == '1')
                    color = 0xFFFFFF;
                else if (tile == '0')
                    color = 0x000000;
                else
                    color = 0x777777;
            }

            draw_tile(cub, x * tile_size, y * tile_size, tile_size, color);
        }
    }
    draw_player_on_minimap(cub, tile_size);
}
