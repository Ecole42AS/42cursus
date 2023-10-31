/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:20 by astutz            #+#    #+#             */
/*   Updated: 2023/10/31 09:37:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


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