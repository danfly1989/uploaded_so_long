/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:16:49 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/16 21:16:51 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

/*verify all lines same length. Use strchr
to modify pointer to position in case of newline
and modify to null terminator instead*/
int	is_rectangle(int fd)
{
	char	*line;
	size_t	len;
	char	*newline;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
	len = ft_strlen(line);
	while (line != NULL)
	{
		if (ft_strlen(line) != len)
			return (free(line), -1);
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			newline = ft_strchr(line, '\n');
			if (newline)
				*newline = '\0';
		}
	}
	return (0);
}

int	valid_char_only(t_game *game)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = game->map_width;
	height = game->map_height;
	x = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (game->map[y][x] != '1' && game->map[y][x] != '0'
				&& game->map[y][x] != 'P' && game->map[y][x] != 'C'
				&& game->map[y][x] != 'E')
			{
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	verify_uniques(t_game *game)
{
	int	x;
	int	y;

	game->player_count = 0;
	game->exit_count = 0;
	x = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				game->player_count++;
			if (game->map[y][x] == 'E')
				game->exit_count++;
			x++;
		}
		y++;
	}
	if (game->player_count == 1 && game->exit_count == 1)
		return (0);
	else
		return (-1);
}

int	verify_collectibles(t_game *game)
{
	int	x;
	int	y;

	game->total_collectibles = 0;
	x = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->total_collectibles++;
			x++;
		}
		y++;
	}
	if (game->total_collectibles <= 0)
		return (-1);
	return (0);
}

/*Ensure top and bottom rows are walls
as well as the first and last column
all the way down*/
int	walled_in(t_game *game)
{
	int	x;
	int	y;
	int	height;
	int	width;

	x = 0;
	y = 0;
	height = game->map_height;
	width = game->map_width;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((y == 0 || (y == height - 1)) && game->map[y][x] != '1')
				return (-1);
			if ((x == 0 || (x == width - 1)) && game->map[y][x] != '1')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
