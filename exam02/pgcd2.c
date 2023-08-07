/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:36:10 by astutz            #+#    #+#             */
/*   Updated: 2023/01/18 13:56:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	unsigned int nb1;
	unsigned int nb2;
	unsigned int n;
	
	nb1 = atoi(av[1]);
	nb2 = atoi(av[2]);
	if (ac == 3)
	{
		while (nb1 != nb2)
		{
			if (nb1 > nb2)
				nb1 -= nb2;
			else
				nb2 -= nb1;
		}
		printf("%d", nb1);
	}
	printf("\n");
}

