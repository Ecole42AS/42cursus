/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:46:39 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 12:35:00 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int nb;
	int nb1;

	if (ac == 3)
	{
		nb = atoi(av[1]);
		nb1 = atoi(av[2]);
		if (nb > 0 && nb1 > 0)
		{
			while (nb != nb1)
			{
				if (nb > nb1)
					nb -= nb1;
				else
					nb1 -= nb;
			}
			printf("%d", nb);
		}
	}
	printf("\n");
}