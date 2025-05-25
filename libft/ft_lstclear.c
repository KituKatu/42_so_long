/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstclear.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/15 13:45:05 by adecheri       #+#    #+#                */
/*   Updated: 2025/02/15 13:45:09 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (!list || !*list)
		return (NULL);
	current = *list;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*list = NULL;
}
