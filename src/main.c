/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:19:00 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/12 20:53:26 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

#define KEYPRESS_MASK 1

/*End window and mlx display*/
int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->player_img)
		free_and_exit(game);
	return (0);
}

/*load all sprites including player by calling
specific player function as well as the load
sprites function from doodling.c*/
int	load_all_sprites(t_game *game)
{
	if (load_sprites(game))
		return (1);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&game->img_width, &game->img_height);
	if (!game->player_img)
	{
		ft_printf("Error: Could not load player.xpm\n");
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		return (1);
	}
	return (0);
}

/*initiate mlx display and create new window*/
int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, TITLE);
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		return (1);
	}
	return (0);
}

/*Ensure that argument given for ./so_long
is a map file of type .ber
If not, print an error to screen*/
int	validate_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map_file.ber>\n", argv[0]);
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error\nMap file must have .ber extension\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game_init(&game);
	if (!validate_args(argc, argv))
		return (1);
	if (init_mlx_and_window(&game))
		return (1);
	if (load_and_print_map(argv[1], &game))
		return (1);
	if (load_all_sprites(&game))
		return (1);
	find_player_start(&game);
	render_map(&game);
	draw_player(&game);
	if (validate_map(&game, argv[1]))
	{
		ft_printf("Error. Invalid map\n");
		free_and_exit(&game);
	}
	mlx_hook(game.win, WINDOW_CLOSE_EVENT, 0, close_window, &game);
	mlx_hook(game.win, KEYPRESS, KEYPRESS_MASK, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
