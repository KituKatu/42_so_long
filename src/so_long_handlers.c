/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long_handlers.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/05 15:41:29 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/05 15:41:30 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

// - Game should close on Esc || clicking cross window frame
// - player should not go through walls
// - window should display moves made
// - player movement WASD / arrows
// - game will exit on player exit
// - window management must remain smooth (minimizing, scroll, switch)

#include "../so_long.h"

void	sl_keyhook(mlx_key_data_t keydown, void *param)
{
	t_gdata	**game;

	game = param;
	if (keydown.action == MLX_PRESS || keydown.action == MLX_REPEAT)
	{
		if (keydown.key == MLX_KEY_ESCAPE)
			mlx_close_window((*game)->mlx);
		if (keydown.key == MLX_KEY_UP || keydown.key == MLX_KEY_W)
			move_pl(game, -1, 0);
		if (keydown.key == MLX_KEY_DOWN || keydown.key == MLX_KEY_S)
			move_pl(game, 1, 0);
		if (keydown.key == MLX_KEY_LEFT || keydown.key == MLX_KEY_A)
			move_pl(game, 0, -1);
		if (keydown.key == MLX_KEY_RIGHT || keydown.key == MLX_KEY_D)
			move_pl(game, 0, 1);
	}
}

void	get_collect(t_map **map, int y, int x)
{
	disable_img_instance((*map)->imgs[2], y, x);
	(*map)->mapgrid[y][x] = SPACE;
	(*map)->coll--;
	if ((*map)->coll == 0)
		(*map)->imgs[3]->instances[0].enabled = true;
}

void	anim_player(t_player *player)
{
	if (player->imgs[0][1]->instances[0].enabled == true)
		player->imgs[0][1]->instances[0].enabled = false;
	else
		player->imgs[0][1]->instances[0].enabled = true;
}

void	move_pl(t_gdata **game, int dely, int delx)
{
	int	x;
	int	y;

	y = (*game)->player->y + dely;
	x = (*game)->player->x + delx;
	if ((*game)->map->mapgrid[y][x] == WALL)
		return ;
	if ((*game)->map->mapgrid[y][x] == COLLECTIBLE)
		get_collect(&(*game)->map, y, x);
	(*game)->player->y = y;
	(*game)->player->x = x;
	(*game)->player->imgs[0][0]->instances[0].y = y * TILE;
	(*game)->player->imgs[0][0]->instances[0].x = x * TILE;
	(*game)->player->imgs[0][1]->instances[0].y = y * TILE;
	(*game)->player->imgs[0][1]->instances[0].x = x * TILE;
	anim_player((*game)->player);
	(*game)->player->stepcount++;
	ft_printf("%d steps\n", (*game)->player->stepcount);
	if (((*game)->map->imgs[3]->instances[0].enabled == true)
		&& ((*game)->map->ex_posx == x) && ((*game)->map->ex_posy == y))
		mlx_close_window((*game)->mlx);
}

// float step;
// step = (float)STEP_SIZE / TILE_SIZE;