/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:15:50 by astutz            #+#    #+#             */
/*   Updated: 2023/08/20 12:17:12 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// /* Stores the excess in the stash for the next reading.*/
// static char	*ft_new_stash(char *stash)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (stash == NULL)
// 		return (NULL);
// 	while (stash[i] != '\0' && stash[i] != '\n')
// 		i++;
// 	if (stash[i] == '\n')
// 		i++;
// 	str = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	while (stash[i] != '\0')
// 	{
// 		str[j] = stash[i];
// 		i++;
// 		j++;
// 	}
// 	free(stash);
// 	str[j] = '\0';
// 	return (str);
// }

// /* Return the line cleaned of excess */
// static char	*ft_extract_line(char *stash)
// {
// 	char	*line;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (stash == NULL)
// 		return (NULL);
// 	while (stash[i] != '\0' && stash[i] != '\n')
// 		i++;
// 	if (stash[i] == '\n')
// 		i++;
// 	line = malloc(sizeof(char) * (i + 1));
// 	if (line == NULL)
// 		return (NULL);
// 	while (j < i)
// 	{
// 		line[j] = stash[j];
// 		j++;
// 	}
// 	line[j] = '\0';
// 	return (line);
// }

// /* reads BUFFER_SIZE elements and adds them to a buffer.
// Return the stash to be managed next. */
// static char	*ft_fill_stash(int fd, char *stash)
// {
// 	char	*buffy;
// 	int		byties;

// 	byties = 1;
// 	buffy = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (buffy == NULL)
// 		return (NULL);
// 	while (byties != 0 && ft_strchr(stash, '\n') == 0)
// 	{
// 		byties = read(fd, buffy, BUFFER_SIZE);
// 		if (byties == -1)
// 		{
// 			free(buffy);
// 			return (NULL);
// 		}
// 		buffy[byties] = '\0';
// 		stash = ft_strjoin_gnl(stash, buffy);
// 	}
// 	free(buffy);
// 	return (stash);
// }

// /*
// Reads a line from a file descriptor.
// @param fd The file descriptor to read from.
// @return On success, the function returns a
// pointer to the line read. On
// error, the function returns NULL.
// The function reads the file descriptor and
// returns a line of text, delimited by
// '\n'. It uses a static linked list to store
// the data read from the file descriptor
// between successive calls. The function returns
// NULL if an error occurs or if the
// end of file is reached.
// */
// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
// 	{
// 		free(stash);
// 		stash = 0;
// 		return (NULL);
// 	}
// 	if (!stash)
// 	{
// 		stash = malloc(sizeof(char) * 1);
// 		stash[0] = 0;
// 	}
// 	stash = ft_fill_stash(fd, stash);
// 	if (*stash == 0)
// 	{
// 		free(stash);
// 		return (stash = 0);
// 	}
// 	line = ft_extract_line(stash);
// 	stash = ft_new_stash(stash);
// 	return (line);
// }

// // int	main(void)
// // {
// // 	int	fd = open("test.txt", O_RDONLY);
// // 	printf("Ceci est la 1 line :\n%s", get_next_line(fd));
// // 	printf("Ceci est la 2 line :\n%s\n", get_next_line(fd));
// // 	printf("Ceci est la 3 line :\n%s\n", get_next_line(fd));
// // 	printf("Ceci est la 4 line :\n%s\n", get_next_line(fd));
// // 	printf("Ceci est la 5 line :\n%s\n", get_next_line(fd));
// // 	printf("Ceci est la 6 line :\n%s\n", get_next_line(fd));
// // 	return (0);
// // }

char *get_next_line(int fd)
{
	char *line;
	static char *stash = NULL;
	

	if (fd < 0 || BUFFER_SIZE == 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return(NULL);
	}
	stash = read_file(fd, stash);
	line = create_line(stash);
	stash = clean_stash(stash);
	return (line);
}

char	*read_file(int fd, char *stash)
{
	char *buffer;
	char *tmp;
	int nb_bytes;

	if (!stash)
		stash = calloc(1, 1);
	buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return(NULL);
	nb_bytes = 1;
	while(nb_bytes > 0 && (!ft_strchr(stash, '\n')))
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

// char *read_file(int fd, char *stash)
// {
//     char *buffer;
//     char *tmp;
//     int nb_bytes;
//     int j; // Ajoutez cette déclaration

//     if (!stash)
//         stash = ft_calloc(1, sizeof(char)); // Utilisez ft_calloc ici
//     buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Utilisez ft_calloc ici
//     if (!buffer)
//         return (NULL);
//     nb_bytes = 1;
//     j = 0; // Initialisez j ici
//     while (nb_bytes > 0 && (!ft_strchr(stash, '\n')))
//     {
//         nb_bytes = read(fd, buffer, BUFFER_SIZE);
//         if (nb_bytes == -1)
//         {
//             free(buffer);
//             free(stash);
//             return (NULL);
//         }
//         buffer[nb_bytes] = '\0';
//         tmp = ft_strjoin(stash, buffer); // Utilisez ft_strjoin ici
//         free(stash);
//         stash = tmp;
//         j += nb_bytes; // Incrémentez j ici
//     }
//     free(buffer); // Libérez la mémoire allouée pour buffer
//     return (stash);
// }

char *create_line(char *stash)
{
	char *line;
	int i;

	i = 0;
	if (!stash)
		return(NULL);
	while(stash[i] != '\n' && stash[i])
		i++;
	line = calloc((i + 2), sizeof(char));//peut etre inversé
	i = 0;
	while(stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (line[i] && line[i] == '\n')
		line[i] = '\n';
	return (line);
}

// char *clean_stash(char *stash)
// {
// 	int i;
// 	int j;
// 	char *new_stash;

// 	i = 0;
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	if (!stash[i])
// 	{
// 		free(stash);
// 		return (NULL);
// 	}
// 		printf("Entering get_next_line\n");
// 	while(stash[i])
// 		i++;
// 	new_stash = calloc((i - j) + 1, sizeof(char));
// 	if (!new_stash)
// 		return (NULL);
// 	i++;
// 	j = 0;
// 	while(stash[i])
// 	{
// 		new_stash[j] = stash[i];
// 		i++;
// 		j++;
// 	}
// 	new_stash[i] = '\0';
// 	free(stash);
// 	return (new_stash);
// }

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

# include <stdio.h>
# include <fcntl.h>
int	main()
{
	int	fd = open("file2.txt", O_RDWR);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	} 
	else 
		printf("no open error!");
	int i = -1;
	while (++i < 19)
	{
		char *line = get_next_line(fd);
		printf("entering the loop");
		printf("RES : |%s|\n", line);
		free(line); // Libérez la mémoire allouée pour line
	}
	return (0);
}
