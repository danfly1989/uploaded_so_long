/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doodling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:11:07 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/16 21:11:39 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

/*Simply replaces the tile with black space. May need to be improved later*/
void	clear_position(t_game *game, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, x * TILE_SIZE + i, y * TILE_SIZE
				+ j, 0x000000);
			j++;
		}
		i++;
	}
}

/*Draw the relevant .xpm image to the correct location
on game->map */
void	draw_tile(t_game *game, int *x, int *y)
{
	if (game->map[*y][*x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall_img, *x
			* TILE_SIZE, *y * TILE_SIZE);
	else if (game->map[*y][*x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit_img, *x
			* TILE_SIZE, *y * TILE_SIZE);
	else if (game->map[*y][*x] == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, *x
			* TILE_SIZE, *y * TILE_SIZE);
	}
}

/*load all sprites except player in case
of distinct functionality*/
int	load_sprites(t_game *game)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&game->img_width, &game->img_height);
	if (!game->wall_img)
	{
		ft_printf("Error: Could not load wall.xpm\n");
		mlx_destroy_window(game->mlx, game->win);
		return (mlx_destroy_display(game->mlx), 1);
	}
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &game->img_width, &game->img_height);
	if (!game->collectible_img)
	{
		ft_printf("Error: Could not load collectible.xpm\n");
		mlx_destroy_window(game->mlx, game->win);
		return (mlx_destroy_display(game->mlx), 1);
	}
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&game->img_width, &game->img_height);
	if (!game->exit_img)
	{
		ft_printf("Error: Could not load exit.xpm\n");
		mlx_destroy_window(game->mlx, game->win);
		return (mlx_destroy_display(game->mlx), 1);
	}
	return (0);
}
