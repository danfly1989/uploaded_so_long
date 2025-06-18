/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:04:01 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/16 21:04:39 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

/*Move accordingly according to corresponding key
OR free everything when escape event is hit*/
void	handle_movement(t_game *game, int keycode, int *new_x, int *new_y)
{
	if (keycode == KEY_ESC)
		free_and_exit(game);
	if (keycode == 'd')
		(*new_x)++;
	else if (keycode == 'a')
		(*new_x)--;
	else if (keycode == 'w')
		(*new_y)--;
	else if (keycode == 's')
		(*new_y)++;
}

/*Physically move player sprite and replace area with black space
if the location is accessible. Exit being inaccessible until all
collectibles are retrieved is hard coded here*/
void	process_move(t_game *game, int *new_x, int *new_y)
{
	if (game->map[*new_y][*new_x] != '1')
	{
		if (game->map[*new_y][*new_x] == 'C')
		{
			game->collected++;
			game->map[*new_y][*new_x] = '0';
		}
		if (game->map[*new_y][*new_x] == 'E')
		{
			if (game->collected != game->total_collectibles)
				return ;
			else
			{
				game->move_count++;
				ft_printf("move count: %d\nYOU HAVE ESCAPED!",
					game->move_count);
				free_and_exit(game);
			}
		}
		clear_position(game, game->player_x, game->player_y);
		game->player_x = *new_x;
		game->player_y = *new_y;
		game->move_count++;
		ft_printf("move count: %d\n", game->move_count);
	}
}

/*Update movement according to keycode
This was formerly one function which was split
into having two helpers. One for handling keys
and the other for processing actual player
movement*/
int	key_press(int keycode, void *game_ptr)
{
	int		new_x;
	int		new_y;
	t_game	*game;

	game = (t_game *)game_ptr;
	new_x = game->player_x;
	new_y = game->player_y;
	handle_movement(game, keycode, &new_x, &new_y);
	process_move(game, &new_x, &new_y);
	draw_player(game);
	return (0);
}
