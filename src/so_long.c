/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/04 17:47:52 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/04 17:47:54 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

// mlx_set_setting(MLX_STRETCH_IMAGE, true);

#include "../so_long.h"

bool	init_player(t_gdata **game)
{
	(*game)->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!(*game)->player)
		return (write(2, "Failed to load Player\n", 22));
	if (init_pl_anim(game))
		return (write(2, "Failed to load Player imgs\n", 27));
	return (0);
}

bool	init_game(t_gdata **game, char *filename)
{
	*game = (t_gdata *)ft_calloc(1, sizeof(t_gdata));
	if (!game)
		return (NULL);
	(*game)->mlx = mlx_init(WIDTH, HEIGHT, "SoLong Project", true);
	if (!(*game)->mlx)
		return (write(2, "No MLX found\n", 13));
	if (init_player(game))
		return (write(2, "No Player found\n", 13));
	if (init_map(filename, game))
		return (write(2, "No Map found\n", 13));
	if (load_img(game))
		return (write(2, "No Imgs\n", 8));
	return (0);
}

bool	render_game(t_gdata **game)
{
	mlx_image_t		*img;
	mlx_texture_t	*icon;
	int				width;
	int				height;

	width = (*game)->map->x_len * TILE;
	height = (*game)->map->y_len * TILE;
	icon = mlx_load_png("./imgs/playerd0.png");
	if (!icon)
		return (write(2, "Icon Failed\n", 12));
	mlx_set_icon((*game)->mlx, icon);
	mlx_delete_texture(icon);
	mlx_set_window_size((*game)->mlx, width, height);
	img = mlx_new_image((*game)->mlx, width, height);
	if (!img || (mlx_image_to_window((*game)->mlx, img, 0, 0) < 0))
		return (write(2, "Failed to load screen\n", 22));
	render_map((*game)->mlx, (*game)->map);
	render_player((*game)->mlx, (*game)->player);
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_gdata	*game;

	game = NULL;
	if (argc != 2)
		ft_exit_error("Invalid Arguments\n");
	if (init_game(&game, argv[1]))
	{
		exit_game(&game, "No Game Found\n");
		safe_free(game);
		exit(EXIT_FAILURE);
	}
	if (render_game(&game))
		exit_game(&game, "Invalid Render\n");
	mlx_key_hook(game->mlx, &sl_keyhook, &game);
	mlx_loop(game->mlx);
	exit_game(&game, "Yay\n");
	safe_free(game);
	return (EXIT_SUCCESS);
}
