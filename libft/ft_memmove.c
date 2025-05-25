/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memmove.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 18:06:50 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/22 18:06:52 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

// moves memory allocated to another address
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest1;
	unsigned char	*src1;

	i = 0;
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (src1 < dest1 && dest1 < src1 + n)
	{
		while (n-- > 0)
			dest1[n] = src1[n];
	}
	else
	{
		while (n-- > 0)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest1);
}
