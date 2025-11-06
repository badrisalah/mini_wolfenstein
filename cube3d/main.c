/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:24:39 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/05 23:57:28 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include  "parsing/wolfnstein/cube.h"

int		game_loop(t_game *cub)
{
	// update(cub->player);
	render(cub);
	draw_minimap(cub);
	mlx_mouse_hide(cub->mlx_ptr, cub->mlx_win);
	// draw_gps_minimap(cub);	
	return (0);
}
// Add to your initialization code (in main or init function):
void init_textures(t_game *cub)
{
    cub->tex_no = malloc(sizeof(t_texture));
    cub->tex_so = malloc(sizeof(t_texture));
    cub->tex_ea = malloc(sizeof(t_texture));
    cub->tex_we = malloc(sizeof(t_texture));
    
    load_texture(cub, cub->tex_no, cub->game_info->north_path);
    load_texture(cub, cub->tex_so, cub->game_info->south_path);
    load_texture(cub, cub->tex_ea, cub->game_info->east_path);
    load_texture(cub, cub->tex_we, cub->game_info->west_path);
}

// Then modify put_texture to select pre-loaded texture instead of loading it

int	initialize_window(t_game *cub)
{
	// cub->map = malloc(MAP_NUM_COLS * MAP_NUM_ROWS);
    // cub->map = map;
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (0);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	cub->img.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	cub->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	player_init(cub, cub->player);
	init_textures(cub);
	if (!mlx_hook(cub->mlx_win, 2, 1L<<0, process_events, cub))
		return (0);
	if (!mlx_hook(cub->mlx_win, 17, 0, cleanup_and_exit, cub))
		return (0);
	if (!mlx_hook(cub->mlx_win, 6, 1L<<6, process_mouse, cub))
		return (0);
	if (!mlx_loop_hook(cub->mlx_ptr, game_loop, cub))
		return (0);
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(cub->mlx_ptr);
	return (1); // add protections later ===> return 0 in each
}

// int	main(int ac, char **av)
// {
// 	t_game		cub;
// 	t_info	config;
	
// 	if (ac != 2)
// 		return (printf("need 2 args !\n"), 1);
// 	if (parser(ac, av, &config))
// 		return (printf("Error\ninput isnt compatible !\n"), 1);
// 	if (config_check(&config))
// 		return (1);
// 	cub.game_info = &config;
// 	if (!initialize_window(&cub))
// 		return (1);
// 	mlx_destroy_window(cub.mlx_ptr, cub.mlx_win);
// 	return (0);
// }


int	main(int ac, char **av)
{
	t_info		config;
	t_garbage	*garb = NULL;
	t_game		cub;

	if (ac != 2)
		return (printf("need 2 args !\n"), 1);
	if (parser(ac, av, &config, &garb)) // pass garb to parser
		return (printf("Error\ninput isnt compatible !\n"), 1);
	if (config_check(&config))
	{
		garbage_clear(&garb);
		return (1);
	}
	cub.game_info = &config;
	int i = 0;
	while (cub.game_info->map[i])
	{
		printf("%s\n", cub.game_info->map[i]);
		i++;
	}
	if (!initialize_window(&cub))
		return (1);
	garbage_clear(&garb);
	return (0);
}