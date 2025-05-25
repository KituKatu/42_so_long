/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long_graph.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/10 11:34:04 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/10 11:34:06 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

// if ((map->mapgrid[i][j] == 'E') || (map->mapgrid[i][j] == '0')
//|| (map->mapgrid[i][j] == 'P') || (map->mapgrid[i][j] == 'C'))

#include "../so_long.h"

bool	load_img(t_gdata **game)
{
	mlx_texture_t	*texture;
	int				i;

	i = 0;
	while (i <= 3)
	{
		if (i == 0)
			texture = mlx_load_png("./imgs/wall.png");
		else if (i == 1)
			texture = mlx_load_png("./imgs/space.png");
		else if (i == 2)
			texture = mlx_load_png("./imgs/coin3.png");
		else if (i == 3)
			texture = mlx_load_png("./imgs/exit.png");
		if (!texture)
			return (write(2, "Loading Texture failed\n", 23));
		(*game)->map->imgs[i] = mlx_texture_to_image((*game)->mlx, texture);
		if (!(*game)->map->imgs[i])
			return (write(2, "Loading Image failed\n", 21));
		mlx_resize_image((*game)->map->imgs[i], TILE, TILE);
		mlx_delete_texture(texture);
		i++;
	}
	return (0);
}

void	disable_img_instance(mlx_image_t *img, int y, int x)
{
	int	i;

	i = img->count - 1;
	if (!img)
		return ;
	while ((i >= 0))
	{
		if ((img->instances[i].x == x * TILE) && (img->instances[i].y == y
				* TILE))
			img->instances[i].enabled = false;
		i--;
	}
}

void	render_map(mlx_t *mlx, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->y_len)
	{
		j = -1;
		while (++j < map->x_len)
		{
			if (map->mapgrid[i][j] == WALL)
				mlx_image_to_window(mlx, map->imgs[0], j * TILE, i * TILE);
			else
			{
				mlx_image_to_window(mlx, map->imgs[1], j * TILE, i * TILE);
				if (map->mapgrid[i][j] == COLLECTIBLE)
					mlx_image_to_window(mlx, map->imgs[2], j * TILE, i * TILE);
				else if (map->mapgrid[i][j] == EXIT)
				{
					mlx_image_to_window(mlx, map->imgs[3], j * TILE, i * TILE);
					disable_img_instance(map->imgs[3], i, j);
				}
			}
		}
	}
	return ;
}

void	render_player(mlx_t *mlx, t_player *player)
{
	mlx_image_to_window(mlx, player->imgs[0][0], player->x * TILE, player->y
		* TILE);
	mlx_image_to_window(mlx, player->imgs[0][1], player->x * TILE, player->y
		* TILE);
	player->imgs[0][1]->instances[0].enabled = false;
}

bool	init_pl_anim(t_gdata **game)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./imgs/playerd1.png");
	if (!texture)
		return (write(2, "Loading Player Text failed\n", 27));
	(*game)->player->imgs[0][0] = mlx_texture_to_image((*game)->mlx, texture);
	if (!(*game)->player->imgs[0][0])
		return (write(2, "Loading Player Img failed\n", 26));
	mlx_delete_texture(texture);
	texture = mlx_load_png("./imgs/playerd2.png");
	if (!texture)
		return (write(2, "Loading Player Text failed\n", 27));
	(*game)->player->imgs[0][1] = mlx_texture_to_image((*game)->mlx, texture);
	if (!(*game)->player->imgs[0][1])
		return (write(2, "Loading  Player Img failed\n", 27));
	mlx_resize_image((*game)->player->imgs[0][0], TILE, TILE);
	mlx_resize_image((*game)->player->imgs[0][1], TILE, TILE);
	mlx_delete_texture(texture);
	return (0);
}
