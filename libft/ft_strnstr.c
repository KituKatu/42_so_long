/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strnstr.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 18:07:01 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/22 18:07:03 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//looks for little string in big string for the first len char in big
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i] == little[j] && i < len)
		{
			i++;
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i - j]);
		}
		i = i - j;
		i++;
	}
	return (NULL);
}

// int main (){
//     char str[50] = "GeeksForFeeks is for programming geeks and freaks.";
// 	char little[5] = "geeks";
//     printf("\nBig: %s\n", str);

//     printf("Little: %s", ft_strnstr(str, little, 4));
//     return (0);
// }