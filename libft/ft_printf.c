/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   libftprintf.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/11 15:27:42 by adecheri       #+#    #+#                */
/*   Updated: 2024/11/11 15:27:44 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int n, int fd, int *count)
{
	char	nmbr;

	if (n < 10)
	{
		nmbr = n + '0';
		write(fd, &nmbr, 1);
		(*count)++;
	}
	else
	{
		ft_putunbr_fd(n / 10, fd, count);
		ft_putunbr_fd(n % 10, fd, count);
	}
}

void	ft_printhex(unsigned int n, char *base, int fd, int *count)
{
	char	nmbr;

	if (n < 16)
	{
		nmbr = base[n];
		write(fd, &nmbr, 1);
		(*count)++;
	}
	else
	{
		ft_printhex(n / 16, base, fd, count);
		ft_printhex(n % 16, base, fd, count);
	}
}

void	ft_printpointr(uintptr_t n, int *count)
{
	if (n == 0)
	{
		write(1, "(nil)", 5);
		*count += 5;
	}
	else
	{
		write(1, "0", 1);
		write(1, "x", 1);
		(*count) += 2;
		ft_printhex2(n, "0123456789abcdef", 1, count);
	}
}

void	check_format(const char c, va_list args, int *count)
{
	if (c == 'c')
		pf_putchar_fd(va_arg(args, int), 1, count);
	else if (c == 's')
		pf_putstr_fd(va_arg(args, char *), 1, count);
	else if (c == 'p')
		ft_printpointr(va_arg(args, uintptr_t), count);
	else if (c == 'd' || c == 'i')
		pf_putnbr_fd(va_arg(args, int), 1, count);
	else if (c == 'u')
		ft_putunbr_fd(va_arg(args, unsigned int), 1, count);
	else if (c == 'x')
		ft_printhex(va_arg(args, uintptr_t), \
		"0123456789abcdef", 1, count);
	else if (c == 'X')
		ft_printhex(va_arg(args, uintptr_t), \
		"0123456789ABCDEF", 1, count);
	else if (c == '%')
	{
		write(1, "%", 1);
		(*count)++;
	}
}

int	ft_printf(const char *str, ...)
{
	int		*count;
	va_list	args;
	int		counted;

	counted = 0;
	count = &counted;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			check_format(*str, args, count);
		}
		else
		{
			pf_putchar_fd(*str, 1, count);
		}
		str++;
	}
	va_end(args);
	return (counted);
	return (0);
}
