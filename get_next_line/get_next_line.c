/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:25:18 by jbranco-          #+#    #+#             */
/*   Updated: 2023/04/19 14:00:33 by jbranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *res)
{
	int		read_bytes;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(res, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(res, buffer);
		free(res);
		res = temp;
	}
	free(buffer);
	return (res);
}

char	*get_myline(char *res)
{
	char	*line;
	size_t	i;

	if (!(*res))
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, res, i + 1);
	if (res[i] == '\n' || res[i] == '\0')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*remove_read(char *res)
{
	size_t	i;
	size_t	j;
	char	*new_res;

	i = 0;
	j = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	new_res = malloc(sizeof(char) * ft_strlen(res) - i + 1);
	if (!new_res)
		return (NULL);
	i++;
	while (res[i])
		new_res[j++] = res[i++];
	new_res[j] = '\0';
	free(res);
	return (new_res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	if (res == NULL)
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			return (NULL);
		res[0] = '\0';
	}
	res = read_file(fd, res);
	if (!res)
		return (NULL);
	line = get_myline(res);
	res = remove_read(res);
	return (line);
}
/*
int	main()
{
	int	fd;
	size_t	lines;
	fd = open("../so_long/maps/map.ber", O_RDONLY);
	lines = 10;
	while (lines-- != 0)
		printf("%s", get_next_line(fd));	
}
*/
