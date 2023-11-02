/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:15:29 by astutz            #+#    #+#             */
/*   Updated: 2023/11/02 11:35:05 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	// if (ac != 2)
	// {
	// 	perror("Should have 2 args");
	// 	return (1);		
	// }
	// parser(av[1])
	(void)ac;
	(void)av;
	char *line;
	
	line = gnl_unempty("/Users/astutz/42cursus/cub3D/test.txt");
	printf("line: %s\n", line);
	
	
	// while (1)
	// {
	// 	line = gnl_unempty("/Users/astutz/42cursus/cub3D/test.txt");
	// 	if (line == NULL)
	// 		break;
	// }
}
