/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf_utils.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/11 16:45:38 by adecheri       #+#    #+#                */
/*   Updated: 2024/11/11 16:45:40 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_putchar_fd(char c, int fd, int *count)
{
	ssize_t	result;

	result = write(fd, &c, 1);
	if (result == -1)
		*count = -1;
	(*count)++;
}

void	pf_putstr_fd(char *s, int fd, int *count)
{
	int	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	write(fd, s, len);
	(*count) += len;
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	else
		return (c);
}

void	pf_putnbr_fd(int n, int fd, int *count)
{
	char	nmbr;

	if (n == -2147483648)
	{
		pf_putstr_fd("-2147483648", fd, count);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		(*count)++;
	}
	if (n < 10)
	{
		nmbr = n + '0';
		write(fd, &nmbr, 1);
		(*count)++;
		return ;
	}
	pf_putnbr_fd(n / 10, fd, count);
	pf_putnbr_fd(n % 10, fd, count);
}
