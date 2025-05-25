/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strdup.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/28 16:11:26 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/28 16:11:27 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//duplicates a string 
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*newstring;

	len = ft_strlen(s) + 1;
	newstring = (char *)malloc(len * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s, len);
	return (newstring);
}
