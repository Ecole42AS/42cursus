/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:31:58 by astutz            #+#    #+#             */
/*   Updated: 2022/12/10 10:55:12 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op.h"



int main(int ac, char **av)
{
	if (ac == 4)
	{
		int i;
		int res;
		
		i = 0;
		if (av[2][i] == 43)
			res = atoi(av[1]) + atoi(av[3]);
		if (av[2][i] == 37)
			res = atoi(av[1]) % atoi(av[3]);
		if (av[2][i] == 42)
			res = atoi(av[1]) * atoi(av[3]);
		if (av[2][i] == 45)
			res = atoi(av[1]) - atoi(av[3]);
		if (av[2][i] == 47)
			res = atoi(av[1]) / atoi(av[3]);
		printf("%d\n", res);
	}
	printf("\n");
}
