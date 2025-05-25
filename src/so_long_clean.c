/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   so_long_clean.c                                    :+:    :+:            */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/07 11:48:48 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/07 11:48:50 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	exit_game(t_gdata **game, const char *str)
{
	write(2, str, ft_strlen(str));
	mlx_terminate((*game)->mlx);
	if (game)
		clean_game(game);
}

void	safe_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}

void	clean_map(t_map **map)
{
	int	y;

	y = 0;
	if ((*map)->mapgrid)
	{
		while ((*map)->mapgrid[y])
			safe_free((*map)->mapgrid[y++]);
	}
	safe_free((*map)->mapgrid);
	safe_free((*map)->mapline);
}

void	clean_game(t_gdata **game)
{
	if ((*game)->player)
		safe_free((*game)->player);
	if ((*game)->map)
	{
		clean_map(&(*game)->map);
		safe_free((*game)->map);
	}
}
