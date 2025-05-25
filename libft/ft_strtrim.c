/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strtrim.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/28 21:37:49 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/28 21:37:50 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	findstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	return (i);
}

int	findend(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				len;
	unsigned int	start;
	unsigned int	end;
	char			*trimstr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = findstart(s1, set);
	end = findend(s1, set);
	len = (end - start) + 1;
	trimstr = ft_substr(s1, start, len);
	return (trimstr);
}

// int main (){
// 	char prestring[] = "Whatever you like me to be,,,,";
// 	char trimset[] = ".,";

// 	printf("%s", ft_strtrim(prestring, trimset));

// }