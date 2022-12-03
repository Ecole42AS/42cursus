/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:46:12 by astutz            #+#    #+#             */
/*   Updated: 2022/12/03 22:46:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char    *_fill_line_buffer(int fd, char *left_c, char *buffer);
static char    *_set_line(char *line);
static char    *ft_strchr(char *s, int c);

char    *get_next_line(int fd)
{
    static char *left_c;
    char        *line;
    char        *buffer;
    
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    /*
     * fd < 0 : this means the file descriptor is invalid
     * BUFFER_SIZE <= 0 : we'll read BUFFER_SIZE characters at a time, we can't read 0 or less character
     * read(fd, 0, 0) < 0 : this check lets us see if the file exists and that it has some content to read from, or event that the file is openable to read, maybe the file descriptor is more than 0, but it was open in 'modify only', that means we can't read it.
     */
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        free(left_c);
        free(buffer);
        left_c = NULL;
        buffer = NULL;
        return (NULL);
    }
    if (!buffer)
        return (NULL);
    line = _fill_line_buffer(fd, left_c, buffer);
    // We have to free the buffer variable here since we'll not be using it later in the function, freeing it prevents memory leaks.
    free(buffer);
    buffer = NULL;
    if (!line)
        return (NULL);
    left_c = _set_line(line);
    return (line);
}

static char *_set_line(char *line_buffer)
{
    char    *left_c;
    ssize_t    i;
    
    i = 0;
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    if (line_buffer[i] == 0 || line_buffer[1] == 0)
        return (NULL);
    left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
    if (*left_c == 0)
    {
        free(left_c);
        left_c = NULL;
    }
    line_buffer[i + 1] = 0;
    return (left_c);
}

static char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
        /* ssize_t type works the same way as siyze_t type, but it can be a negative number, something that size_t can't do.
        * Since most of the system function we'll be using return -1 to signify errors, it could be useful to be able to store negative numbers
        */
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		// if b_read is -1, it means there was an error reading the file descriptor, so we free left_c and return NULL.
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		// if b_read is 0, this surely means we read the whole file so there-s no need to stay in the loop
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}
