/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: adecheri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/22 14:05:50 by adecheri       #+#    #+#                */
/*   Updated: 2024/11/22 14:05:52 by adecheri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//processes full line to update return_line and leftover
char	*extract_line(char *line_buffer, char *leftover)
{
	char	*return_line;
	char	*has_newline;

	has_newline = ft_strchr(line_buffer, '\n');
	if (has_newline)
	{
		return_line = ft_substr(line_buffer, 0,
				(has_newline - line_buffer + 1));
		if (return_line == NULL)
			return (free(line_buffer), NULL);
		ft_strlcpy(leftover, (has_newline + 1), ft_strlen(has_newline));
		free(line_buffer);
		return (return_line);
	}
	else
	{
		if (ft_strchr(leftover, '\n') == NULL)
			leftover[0] = '\0';
	}
	return (line_buffer);
}

//reads in full lines
char	*read_and_store(int fd, char *full_line, char *buffer)
{
	int		bytesread;
	char	*temp;

	bytesread = 1;
	while (ft_strchr(full_line, '\n') == NULL)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (free(full_line), NULL);
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		temp = full_line;
		full_line = ft_strjoin(full_line, buffer);
		if (full_line == NULL)
			return (free(temp), NULL);
		free(temp);
		temp = NULL;
	}
	return (full_line);
}

char	*get_next_line(int fd)
{
	char		*full_line;
	char		*return_line;
	static char	leftover[BUFFER_SIZE + 1];

	if (fd < 0)
		return (NULL);
	full_line = ft_strdup(leftover);
	if (full_line == NULL)
		return (NULL);
	full_line = read_and_store(fd, full_line, leftover);
	if (full_line == NULL)
		return (leftover[0] = 0, NULL);
	return_line = extract_line(full_line, leftover);
	if (return_line == NULL || (return_line[0] == '\0' && leftover[0] == '\0'))
	{
		free(return_line);
		return (NULL);
	}
	return (return_line);
}

// int main()
// {
// 	int fd;
//  // int open (const char *pathname, int flags);
// 	fd = -1; //open("testing.txt", O_RDWR);
// 	char *ln;
// 	while ((ln = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", ln);
// 		free(ln);
// 	}
// 	close(fd);
// }