/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isdigit.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 12:53:41 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/08 12:53:46 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
