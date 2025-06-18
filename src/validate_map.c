/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:30:55 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/17 14:31:45 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Takes an original map array
and returns a copy through the logic
of calling ft_strdup on each string
pre-increment of i is a trick to save
one line and appease norminette
by not requiring i++ in body*/
char	**copy_map(char **original)
{
	char	**copy;
	int		i;
	int		height;

	height = 0;
	if (!original)
		return (NULL);
	while (original[height])
		height++;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (original[++i])
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

/*Uses a dfs mechanism to simulate possible player movement
The key is that all four recursive cases are called in a single run
This means that only when all cases have fully ended (legale moves exhausted)
will the algorithm truly end*/
void	flood_fill(t_game *game, int x, int y, char **test_map)
{
	if (x < 0 || x >= game->map_width)
		return ;
	if (y < 0 || y >= game->map_height)
		return ;
	if (test_map[y][x] == '1')
		return ;
	if (test_map[y][x] == 'X')
		return ;
	test_map[y][x] = 'X';
	flood_fill(game, x + 1, y, test_map);
	flood_fill(game, x - 1, y, test_map);
	flood_fill(game, x, y + 1, test_map);
	flood_fill(game, x, y - 1, test_map);
}

/*Contrast locations of collectibles and exit on game map
with that of marked immovable locations on test map*/
int	check_reachability(t_game *game, char **test_map)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if ((game->map[y][x] == 'C' || game->map[y][x] == 'E')
				&& test_map[y][x] != 'X')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

/*Run ths simple checks first before checking whether
objective is in fact reachable by calling flood fill
*/
int	validate_map(t_game *game, char *filename)
{
	int		fd;
	char	**map_copy;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (is_rectangle(fd) < 0)
		return (close(fd), -1);
	close(fd);
	map_copy = copy_map(game->map);
	if (!map_copy)
		return (-1);
	if (verify_collectibles(game) < 0)
		return (free_map(map_copy), -1);
	if (verify_uniques(game) < 0)
		return (free_map(map_copy), -1);
	if (valid_char_only(game) < 0)
		return (free_map(map_copy), -1);
	if (walled_in(game) < 0)
		return (free_map(map_copy), -1);
	find_player_start(game);
	flood_fill(game, game->player_x, game->player_y, map_copy);
	if (check_reachability(game, map_copy))
		return (free_map(map_copy), -1);
	return (free_map(map_copy), 0);
}
