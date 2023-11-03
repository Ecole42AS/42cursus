/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:08:13 by astutz            #+#    #+#             */
/*   Updated: 2023/11/02 11:56:09 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE == 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = create_line(stash);
	stash = clean_stash(stash);
	return (line);
}

void	*ft_malloc_return(int size, size_t type)
{
	void	*ptr;

	ptr = ft_calloc(size + 1, type);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		nb_bytes;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_malloc_return((BUFFER_SIZE + 1), sizeof(char));
	nb_bytes = 1;
	while (nb_bytes > 0 && (!ft_strchr(stash, '\n')))
	{
		nb_bytes = read(fd, buffer, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[nb_bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*create_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;
	int		stash_len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	stash_len = 0;
	while (stash[stash_len])
		stash_len++;
	new_stash = malloc((stash_len - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

// int main() {
//     int fd = open("test.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Erreur lors de l'ouverture du fichier");
//         return 1;
//     }

//     char *line;
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("Ligne lue : %s\n", line);
//         free(line);
//     }

//     close(fd);
//     return 0;
// }