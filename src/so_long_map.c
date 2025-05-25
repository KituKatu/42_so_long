/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long_map.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/05 15:41:02 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/05 15:41:04 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

//  - Map must be rectangular (width > height)
//  - 2D view -> profile
//  - Map must:
//     - surrounded by walls (1)
//     - have open space to traverse (0)
//     - have 1 player starting point (P)
//     - have 1 exit (E)
//     - have >1 collectable (C)
//  - have valid route to exit

#include "../so_long.h"

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

bool	init_map(char *filename, t_gdata **game)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".ber", 5))
		return (write(2, "Invalid Mapname\n", 16));
	filename = ft_strjoin("./maps/", filename);
	(*game)->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!(*game)->map)
		return (write(2, "Calloc Fail\n", 12));
	(*game)->map = read_map_file((*game)->map, filename);
	if ((*game)->map->fd < 0)
		return (safe_free(filename), write(2, "Map Not Read\n", 14));
	(*game)->map->mapgrid = ft_split((*game)->map->mapline, '\n');
	(*game)->map->x_len = ft_strlen((*game)->map->mapgrid[0]);
	if (validate_map((*game)->map, &(*game)->player))
		return (safe_free(filename), write(2, "Invalid Map\n", 12));
	if (map_copy_val(game))
		return (safe_free(filename), write(2, "Copy Error\n", 11));
	safe_free(filename);
	return (0);
}

t_map	*read_map_file(t_map *map, const char *filename)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp2 = NULL;
	map->fd = open(filename, O_RDONLY);
	if (map->fd == -1)
		return (map);
	tmp1 = get_next_line(map->fd);
	while (tmp1 != NULL)
	{
		if (tmp2 != NULL)
		{
			tmp3 = map->mapline;
			if (map->mapline == NULL)
				map->mapline = ft_strjoin(tmp2, tmp1);
			else
				map->mapline = ft_strjoin(map->mapline, tmp1);
			(free(tmp2), free(tmp3));
		}
		tmp2 = ft_strdup(tmp1);
		(free(tmp1), map->y_len++);
		tmp1 = get_next_line(map->fd);
	}
	return (free(tmp2), close(map->fd), map);
}

t_map	*validate_mapline(t_map *map, t_player **player, int i, int j)
{
	if (i == 0 && map->mapgrid[i][j] != WALL)
		return (NULL);
	else if ((j == 0 && map->mapgrid[i][j] != WALL) || (j == map->x_len
			&& map->mapgrid[i][j] != WALL))
		return (NULL);
	else if (map->mapgrid[i][j] == PLAYER)
	{
		(*player)->count++;
		(*player)->x = j;
		(*player)->y = i;
	}
	else if (map->mapgrid[i][j] == COLLECTIBLE)
		map->coll++;
	else if (map->mapgrid[i][j] == EXIT)
	{
		map->ex_pos++;
		map->ex_posx = j;
		map->ex_posy = i;
	}
	return (map);
}

bool	validate_map(t_map *map, t_player **player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->y_len - 1)
	{
		j = -1;
		if ((ft_strlen(map->mapgrid[i]) != (size_t)map->x_len)
			|| (map->x_len == map->y_len))
			return (write(2, "Error map measurements\n", 23));
		while (map->mapgrid[i][++j] != '\0')
		{
			if ((validate_mapline(map, player, i, j)) == NULL)
				return (write(2, "Error Walls\n", 12));
		}
	}
	if (ft_strncmp(map->mapgrid[0], map->mapgrid[i], map->x_len) != 0)
		return (write(2, "Error bottom walls\n", 19));
	if ((*player)->count != 1 || map->ex_pos != 1 || map->coll < 1)
		return (write(2, "Error invalid map\n", 18));
	return (0);
}
