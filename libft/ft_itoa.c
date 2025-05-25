/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_itoa.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/28 21:40:27 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/28 21:40:29 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

char	*safemalloc(int len)
{
	char	*strmem;

	strmem = (char *)malloc((len + 1) * sizeof(char));
	if (strmem == NULL)
	{
		return (NULL);
	}
	strmem[len] = '\0';
	return (strmem);
}

char	*fillstr(int n, char *strng, int len, int isneg)
{
	while (n > 9)
	{
		strng[len - 1] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	strng[isneg] = n + '0';
	if (isneg)
		strng[0] = '-';
	return (strng);
}

// converts int value to equiv string
char	*ft_itoa(int n)
{
	char	*strng;
	int		digits;
	int		len;
	int		isneg;

	len = 1;
	isneg = 0;
	if (n < 0)
	{
		isneg = 1;
		n = n * -1;
		len++;
	}
	digits = n;
	while (digits > 9)
	{
		len++;
		digits /= 10;
	}
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	strng = safemalloc(len);
	if (strng == NULL)
		return (NULL);
	return (fillstr(n, strng, len, isneg));
}
