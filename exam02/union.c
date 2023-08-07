/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:01:11 by astutz            #+#    #+#             */
/*   Updated: 2022/12/19 16:26:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int check_doubles(char *str, int c, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (ac == 3)
	{
		while (av[1][i])
			i++;
		while (av[2][j])
			av[1][i++] = av[2][j++];
		i--;
		while (k <= i)
		{
			if (check_doubles(av[1], av[1][k], k) == 0)
				write(1, &av[1][k], 1);
			k++;
		}
	}
	write(1, "\n", 1);
}