/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_exit_error.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/20 16:26:54 by adecheri       #+#    #+#                */
/*   Updated: 2025/05/20 16:26:56 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
