/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:24:39 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 22:29:18 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_loop(t_game *cub)
{
	render(cub);
	draw_minimap(cub);
    cub->time += 1.0f;
	update_and_draw_overlay(cub, cub->time);
	mlx_mouse_hide(cub->mlx_ptr, cub->mlx_win);
	return (0);
}


void init_textures(t_game *cub, t_garbage **garb_list)
{
    cub->tex_no = ft_malloc(sizeof(t_texture), garb_list);
    cub->tex_so = ft_malloc(sizeof(t_texture), garb_list);
    cub->tex_ea = ft_malloc(sizeof(t_texture), garb_list);
    cub->tex_we = ft_malloc(sizeof(t_texture), garb_list);
    cub->overlay = ft_malloc(sizeof(t_texture), garb_list);
    load_texture(cub, cub->tex_no, cub->info->north_path);
    load_texture(cub, cub->tex_so, cub->info->south_path);
    load_texture(cub, cub->tex_ea, cub->info->east_path);
    load_texture(cub, cub->tex_we, cub->info->west_path);
    load_texture(cub, cub->overlay, "textures/hud.xpm");
}


int	initialize_window(t_game *cub, t_garbage **garb_lst)
{
	cub->player = ft_malloc(sizeof(t_player), garb_lst);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	cub->img.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	cub->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if (!cub->rays)
		return (0);
	player_init(cub, cub->player);
	init_textures(cub, garb_lst);
	mlx_hook(cub->mlx_win, 2, 1L << 0, process_events, cub);
	mlx_hook(cub->mlx_win, 17, 0, cleanup_and_exit, cub);
	mlx_hook(cub->mlx_win, 6, 1L << 6, process_mouse, cub);
	mlx_loop_hook(cub->mlx_ptr, game_loop, cub);
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(cub->mlx_ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_info		config;
	t_garbage	*garb;
	t_game		cub;

	garb = NULL;
	if (ac != 2)
		return (printf("Error\nneed 2 args !\n"), 1);
	if (parser(ac, av, &config, &garb))
	{
		garbage_clear(&garb);
		return (printf("Error\ninput isnt compatible !\n"), 1);
	}
	if (config_check(&config))
		return (garbage_clear(&garb), 1);
	cub.info = &config;
	cub.garb = &garb;
	cub.time = 0;
	if (!initialize_window(&cub, &garb))
	{
		garbage_clear(&garb);
		return (1);
	}
	garbage_clear(&garb);
	return (0);
}
