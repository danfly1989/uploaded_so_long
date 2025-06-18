/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:46:59 by daflynn           #+#    #+#             */
/*   Updated: 2025/06/12 20:53:43 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

// int		map_width = 0;
// int		map_height = 0;

int	load_and_print_map(const char *filename, t_game *game)
{
	int	i;

	i = 0;
	game->map = load_map(filename, game);
	if (!game->map)
	{
		ft_printf("Error loading map: %s\n", filename);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		return (1);
	}
	while (game->map[i])
	{
		ft_printf("map[%d]: %s\n", i, game->map[i]);
		i++;
	}
	return (0);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, &x, &y);
			x++;
		}
		y++;
	}
}

/*Count the number of lines from top to bottom
on the map file*/
int	count_map_lines(t_game *game, const char *filename)
{
	int		line_count;
	int		fd;
	char	*line;

	game->map_width = 0;
	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		if (game->map_width == 0)
			game->map_width = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

int	read_lines_to_array(int fd, char **temp_map, int line_count)
{
	char	*line;
	int		i;

	i = 0;
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL && i < line_count)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		temp_map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	temp_map[i] = NULL;
	close(fd);
	return (0);
}

/*uses get_next_line to create map
 *from ber file*/
char	**load_map(const char *filename, t_game *game)
{
	int		fd;
	char	**temp_map;
	int		i;
	int		line_count;

	i = 0;
	line_count = count_map_lines(game, filename);
	if (line_count < 0)
		return (NULL);
	game->map_height = line_count;
	temp_map = malloc(sizeof(char *) * (line_count + 1));
	if (!temp_map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (read_lines_to_array(fd, temp_map, line_count) < 0)
	{
		free(temp_map);
		return (NULL);
	}
	return (temp_map);
}
