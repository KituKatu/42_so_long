/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_split.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/28 21:38:24 by adecheri       #+#    #+#                */
/*   Updated: 2024/10/28 21:38:26 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

size_t	count_tokens(char const *s, char c)
{
	int		i;
	bool	inside_token;
	size_t	tokens;

	i = 0;
	tokens = 0;
	inside_token = 0;
	while (s[i] != '\0')
	{
		inside_token = 0;
		while (s[i] != c && s[i] != '\0')
		{
			if (!inside_token)
			{
				inside_token = 1;
				tokens++;
			}
			i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (tokens);
}

bool	safe_malloc(char **token_array, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_array[position] = malloc(buffer);
	if (token_array[position] == NULL)
	{
		while (i < position)
		{
			free(token_array[i++]);
		}
		free(token_array);
		return (false);
	}
	return (true);
}

int	fill_array(char **token_array, char const *s, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			s++;
		while (*s != delimeter && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (safe_malloc(token_array, i, (len + 1) * sizeof(char)) == false)
				return (1);
			ft_strlcpy(token_array[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**token_array;
	size_t	tokens;

	tokens = 0;
	if (s == NULL)
		return (NULL);
	tokens = count_tokens(s, c);
	token_array = malloc((tokens + 1) * sizeof(char *));
	if (token_array == NULL)
		return (NULL);
	token_array[tokens] = NULL;
	if (fill_array(token_array, s, c))
		return (NULL);
	return (token_array);
}
// int main(){

// 	char *string;
// 	char **new_array;
// 	string = "hello! second";
// 	new_array = ft_split(string, ' ');
// 	printf("%s | %s | %s |", new_array[0], new_array[1], new_array[2]);
// 	free(new_array);
// 	return (0);
// }