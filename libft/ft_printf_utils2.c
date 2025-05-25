/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf_utils2.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/26 15:16:10 by adecheri       #+#    #+#                */
/*   Updated: 2024/11/26 15:16:12 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printhex2(uintptr_t n, char *base, int fd, int *count)
{
	char	nmbr;

	if (n < 16)
	{
		nmbr = base[n];
		write(fd, &nmbr, 1);
		(*count)++;
		return ;
	}
	else
	{
		ft_printhex2(n / 16, base, fd, count);
		ft_printhex2(n % 16, base, fd, count);
	}
}
