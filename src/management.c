/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:27:25 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/18 09:31:55 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include <mlx.h>

/*Free anything potentially malloced from the
game struct*/
void	free_and_exit(t_game *game)
{
	if (!game)
		exit(0);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->map)
		free_map(game->map);
	exit(0);
}

/*initialise all components of game struct
Some redundancy exists here, but safety first!*/
void	game_init(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->move_count = 0;
	game->collected = 0;
	game->total_collectibles = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->player_img = NULL;
	game->wall_img = NULL;
	game->exit_img = NULL;
	game->collectible_img = NULL;
}

/*Free map line by line before freeing
the whole 2d array*/
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
