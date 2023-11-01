/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:20 by astutz            #+#    #+#             */
/*   Updated: 2023/11/01 09:44:24 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parser(char *file)
{
	char **tmp;
	char *line;
	int tab_size;
	int string_size;
    int fd;

	tmp = NULL;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, strerror(errno), ft_strlen(errno));
		return(1);
	}
	tmp = ft_malloc_failed_msg(tab_size, sizeof(char *));
	*tmp = ft_malloc_failed_msg(string_size, sizeof(char));
	while (get_next_line(fd))
	{
		
	}
}


void print(char *str)
{
	printf("%s", str);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int i;

	i = 4;
	while (i)
	{
		print("hello world");
		i--;
	}
}