/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long_map2.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/08 13:37:16 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/08 13:37:18 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_map	*copy_map(t_map *map)
{
	t_map	*map_copy;

	map_copy = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map_copy)
	{
		write(2, "No Map Copy\n", 12);
		return (NULL);
	}
	map_copy->mapline = ft_strdup(map->mapline);
	if (map_copy->mapline == NULL)
	{
		(safe_free(map_copy), write(2, "Invalid Copy\n", 13));
		return (NULL);
	}
	map_copy->mapgrid = ft_split(map_copy->mapline, '\n');
	map_copy->x_len = map->x_len;
	map_copy->y_len = map->y_len;
	map_copy->ex_count = map->ex_count;
	map_copy->ex_posx = map->ex_posx;
	map_copy->ex_posy = map->ex_posy;
	return (map_copy);
}

void	validate_map_path(t_map *map, int posx, int posy)
{
	if (map->mapgrid[posy][posx] == WALL)
		return ;
	else if (map->mapgrid[posy][posx] == COLLECTIBLE
		|| map->mapgrid[posy][posx] == SPACE
		|| map->mapgrid[posy][posx] == PLAYER
		|| map->mapgrid[posy][posx] == EXIT)
	{
		map->mapgrid[posy][posx] = '.';
		validate_map_path(map, posx + 1, posy);
		validate_map_path(map, posx, posy + 1);
		validate_map_path(map, posx - 1, posy);
		validate_map_path(map, posx, posy - 1);
	}
	return ;
}

bool	check_map_path(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->y_len)
	{
		j = 0;
		while (map->mapgrid[i][j] != '\0')
		{
			if (map->mapgrid[i][j] == EXIT || map->mapgrid[i][j] == COLLECTIBLE)
				return (write(2, "Invalid Map Path\n", 17));
			j++;
		}
		i++;
	}
	return (0);
}

bool	map_copy_val(t_gdata **game)
{
	t_map	*map_copy;

	map_copy = NULL;
	map_copy = copy_map((*game)->map);
	if (!map_copy)
		return (1);
	validate_map_path(map_copy, (*game)->player->x, (*game)->player->y);
	if (check_map_path(map_copy))
	{
		(clean_map(&map_copy), safe_free(map_copy));
		return (1);
	}
	(clean_map(&map_copy), safe_free(map_copy));
	return (0);
}
