/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:55:13 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/12 20:59:01 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

/*find the start location of the player*/
void	find_player_start(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				ft_printf("Player found at: (%d, %d)\n", x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	ft_printf("Player not found in map!\n");
}

/*Draw the player sprite*/
void	draw_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->player_img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
