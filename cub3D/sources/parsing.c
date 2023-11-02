/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:20 by astutz            #+#    #+#             */
/*   Updated: 2023/11/02 11:49:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *gnl_unempty(char *file)
{
	int fd;
	char *line;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return(1);
	}
	// line = get_next_line(fd);
	// while (line)
	// {
	// 	printf("line: %s\n", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	line = get_next_line(fd);	
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}	
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	return (line);
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
