/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memset.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 15:14:48 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/21 15:14:50 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	char	*start;

	ptr = (char *)s;
	start = ptr;
	while (n > 0)
	{
		*ptr = (char)c;
		ptr++;
		n--;
	}
	return (start);
}

// int main (){
//     char str[50] = "GeeksForFeeks is for programming geeks.";
//     printf("\nBefore memset(): %s\n", str);

//     ft_memset(str + 13, '.', 8*sizeof(char));

//     printf("After memset(): %s", str);
//     return (0);
// }