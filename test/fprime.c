/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:50:13 by astutz            #+#    #+#             */
/*   Updated: 2023/01/02 15:25:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	nb;

	if (argc == 2)
	{
		i = 2;
		nb = atoi(argv[1]);
		if (nb == 1)
			printf("1");
		while (i <= nb)
		{
			if (nb % i == 0)
			{
				printf("%d", i);
				if (nb == i)
					break ;
				printf("*");
				nb /= i;
				i = 1;
			}
			i++;
		}
	}
	printf("\n");
	return (0);
}