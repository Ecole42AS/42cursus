/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:20 by astutz            #+#    #+#             */
/*   Updated: 2024/01/13 13:16:40 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*Get next unempty line of fd*/
char *gnl_unempty(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/*Return fd, -1 if open failed*/
int	open_file(char *file_path)
{
	int fd = open(file_path, O_RDONLY);

	if (fd == -1)
		ft_putstr_fd(strerror(errno), 2);
	return (fd);
}

void free_split(char **split_result)
{
	int i;

	i = 0;
    if (split_result)
    {
        while (split_result[i] != NULL)
        {
            free(split_result[i]);
			i++;
        }
        free(split_result);
    }
}

void	free_texture(t_texture *texture)
{
	free(texture->NO_texture_path);
	free(texture->SO_texture_path);
	free(texture->WE_texture_path);
	free(texture->EA_texture_path);
	free(texture);
}

// int	parser(char *file)
// {
// 	char **tmp;
// 	char *line;
// 	int tab_size;
// 	int string_size;
//     int fd;

// 	tmp = NULL;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		write(2, strerror(errno), ft_strlen(errno));
// 		return(1);
// 	}
// 	tmp = ft_malloc_failed_msg(tab_size, sizeof(char *));
// 	*tmp = ft_malloc_failed_msg(string_size, sizeof(char));
// 	while (get_next_line(fd))
// 	{

// 	}
// }

	// int main(int ac, char **av)
	// {
	//     int fd = open("/Users/astutz/42cursus/cub3D/test.txt", O_RDONLY);

	// 	if (fd == -1)
	// 	{
	// 		ft_putstr_fd(strerror(errno), 2);
	// 		return(1);
	// 	}

	//     char *line;
	//     while ((line = gnl_unempty(fd)) != NULL) 
	// 	{
	// 		if (line[strlen(line) - 1] == '\n')
	//             line[strlen(line) - 1] = '\0';
	//         printf("Ligne non vide : %s\n", line);
	//         free(line);
	//     }

	//     close(fd);

	//     return 0;
	// }