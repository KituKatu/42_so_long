/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long.h                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/04 17:49:01 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/04 17:49:03 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 544
# define HEIGHT 400
# define WALL '1'
# define SPACE '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define TILE 64
# define STEP_SIZE 4

typedef struct s_player
{
	int			count;
	int			x;
	int			y;
	mlx_image_t	*imgs[1][2];
	int			stepcount;
}				t_player;

typedef struct s_map
{
	int			fd;
	int			x_len;
	int			y_len;
	char		*mapline;
	char		**mapgrid;
	mlx_image_t	*imgs[5];
	int			coll;
	int			ex_pos;
	int			ex_posx;
	int			ex_posy;

}				t_map;

typedef struct s_gdata
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	*player;
}				t_gdata;

// typedef struct s_collect
// {
//     int instance;
//     int x;
//     int y;
//     mlx_t *img;
//     void* next;

// } t_collect;

void			safe_free(void *ptr);
void			exit_game(t_gdata **game, const char *str);
bool			init_player(t_gdata **game);
bool			init_pl_anim(t_gdata **game);
bool			init_map(char *filename, t_gdata **game);
t_map			*read_map_file(t_map *map, const char *filename);
t_map			*copy_map(t_map *map);
bool			validate_map(t_map *map, t_player **player);
t_map			*validate_mapline(t_map *map, t_player **player, int i, int j);
void			validate_map_path(t_map *map, int posx, int posy);
bool			check_map_path(t_map *map);
bool			init_game(t_gdata **game, char *filename);
bool			load_img(t_gdata **game);
void			render_map(mlx_t *mlx, t_map *map);
void			render_player(mlx_t *mlx, t_player *player);
void			anim_player(t_player *player);
void			get_collect(t_map **map, int y, int x);
void			move_pl(t_gdata **game, int dely, int delx);
void			sl_keyhook(mlx_key_data_t keydown, void *param);
void			disable_img_instance(mlx_image_t *img, int y, int x);
void			clean_map(t_map **map);
void			clean_game(t_gdata **game);
// void gen_hook(void *param);
// void mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param);

#endif
