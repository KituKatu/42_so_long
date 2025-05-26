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

bool	validate_map_line(t_map *map)
{
	int	i;

	i = 0;
	if (!map->mapline)
		return (write(2, "Empty MapLine\n", 14));
	else if (!ft_strchr(map->mapline, '\n'))
		return (write(2, "No Grid found\n", 10));
	while (map->mapline[i])
	{
		if (map->mapline[i] != WALL && map->mapline[i] != SPACE
			&& map->mapline[i] != PLAYER && map->mapline[i] != EXIT
			&& map->mapline[i] != COLLECTIBLE && map->mapline[i] != '\n')
			return (write(2, "Wrong Map Tiles\n", 16));
		i++;
	}
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
	(*game)->map->fd = open(filename, O_RDONLY);
	if ((*game)->map->fd < 0)
		return (safe_free(filename), write(2, "Map Not Read\n", 14));
	if (read_map_file(game))
		return (safe_free(filename), 1);
	if (validate_map_line((*game)->map))
		return (safe_free(filename), 1);
	(*game)->map->mapgrid = ft_split((*game)->map->mapline, '\n');
	(*game)->map->x_len = ft_strlen((*game)->map->mapgrid[0]);
	if (validate_map((*game)->map, &(*game)->player))
		return (safe_free(filename), write(2, "Invalid Map\n", 12));
	if (map_copy_val(game))
		return (safe_free(filename), write(2, "Copy Error\n", 11));
	safe_free(filename);
	return (0);
}

bool	read_map_file(t_gdata **game)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp1 = get_next_line((*game)->map->fd);
	if (!tmp1 || ft_strchr(tmp1, '\n') == NULL)
		return (safe_free(tmp1), write(2, "Empty Map\n", 10));
	while (tmp1 != NULL)
	{
		if (tmp2 != NULL)
		{
			tmp3 = (*game)->map->mapline;
			if ((*game)->map->mapline == NULL)
				(*game)->map->mapline = ft_strjoin(tmp2, tmp1);
			else
				(*game)->map->mapline = ft_strjoin((*game)->map->mapline, tmp1);
			(free(tmp2), free(tmp3));
		}
		tmp2 = ft_strdup(tmp1);
		(free(tmp1), (*game)->map->y_len++);
		tmp1 = get_next_line((*game)->map->fd);
	}
	return (free(tmp2), close((*game)->map->fd), 0);
}

t_map	*validate_map_row(t_map *map, t_player **player, int i, int j)
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
		if (ft_strlen(map->mapgrid[i]) != (size_t)map->x_len)
			return (write(2, "Error map measurements\n", 23));
		while (map->mapgrid[i][++j] != '\0')
		{
			if ((validate_map_row(map, player, i, j)) == NULL)
				return (write(2, "Error Walls\n", 12));
		}
	}
	if ((ft_strlen(map->mapgrid[0]) != ft_strlen(map->mapgrid[i]))
		|| (ft_strncmp(map->mapgrid[0], map->mapgrid[i], map->x_len) != 0))
		return (write(2, "Error bottom walls\n", 19));
	if ((*player)->count != 1 || map->ex_pos != 1 || map->coll < 1)
		return (write(2, "Error invalid map\n", 18));
	return (0);
}
