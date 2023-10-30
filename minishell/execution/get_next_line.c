/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:42:10 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/11/29 11:42:22 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "pipex.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

void	*ft_memcpy(char *d, int spot, int buf)
{
	int	i;

	i = 0;
	while (i + spot < buf)
	{
		d[i] = d[i + spot];
		i++;
	}
	while (i < buf && d[i] != '\0')
	{
		d[i] = '\0';
		i++;
	}
	return (d);
}

char	*concat(char *s1, char c, int *len)
{
	char	*str;
	int		i;

	str = ft_calloc((*len + 1), sizeof(char));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < *len)
	{
		if (s1[i] == '\n')
			break ;
		str[i] = s1[i];
		i++;
	}
	str[*len] = c;
	free(s1);
	*len += 1;
	return (str);
}

char	*next_step(char *ret, int *len, char *line, int i)
{
	ft_memcpy(line, i + 1, BUFFER_SIZE);
	return (concat(ret, '\0', len));
}

char	*find_line(int fd, char *line, char *ret, int end)
{
	int		i;
	int		len;

	len = 0;
	while (end > 0)
	{
		i = -1;
		while (++i < end && line[i] != '\0')
		{
			ret = concat(ret, line[i], &len);
			if (line[i] == '\n')
				return (next_step(ret, &len, line, i));
		}
		ft_memcpy(line, i + 1, BUFFER_SIZE);
		end = read(fd, line, BUFFER_SIZE);
	}
	if (len != 0)
	{
		ret = next_step(ret, &len, line, i);
		return (ret);
	}
	free(ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*ret;
	int			end;

	if (!(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0))
	{
		end = BUFFER_SIZE;
		ret = ft_calloc(1, sizeof(char));
		if (ret == NULL)
			return (NULL);
		if (!line)
		{
			line = ft_calloc(BUFFER_SIZE, sizeof(char) + 1);
			if (line == NULL)
				return (NULL);
			end = read(fd, line, BUFFER_SIZE);
		}
		ret = find_line(fd, line, ret, end);
		if (ret != NULL)
			return (ret);
	}
	free(line);
	line = NULL;
	return (NULL);
}
