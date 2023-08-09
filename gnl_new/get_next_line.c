/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:08:13 by astutz            #+#    #+#             */
/*   Updated: 2023/08/09 21:28:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char *line;
	static char *stash;
	
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

// char	*read_file(int fd, char *stash)
// {
// 	char *buffer;
// 	char *tmp;
// 	int nb_bytes;

// 	if (!stash)
// 		stash = calloc(1, 1);
// 	buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
// 	if (!buffer)
// 		return(NULL);
// 	nb_bytes = 1;
// 	while(nb_bytes > 0 && (!ft_strchr(stash, '\n')))
// 	{
// 		nb_bytes = read(fd, buffer, BUFFER_SIZE);
// 		if (nb_bytes == -1)
// 		{
// 			free(buffer);
// 			free(stash);
// 			return (NULL);
// 		}
// 		buffer[nb_bytes] = '\0';
// 		tmp = ft_strjoin(stash, buffer);
// 		free(stash);
// 		stash = tmp;
// 	}
// 	return (stash);
// }

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

char *clean_stash(char *stash)
{
	int i;
	int j;
	char *new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	while(stash[i])
		j++;
	new_stash = calloc((i - j) + 1, sizeof(char));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while(stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	new_stash[i] = '\0';
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
	int i = 0;
	while (i++ < 19)
		//get_next_line(fd);
		printf("RES : |%s|\n", get_next_line(fd));
	close(fd);
	return (0);
}
