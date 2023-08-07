/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:02:10 by astutz            #+#    #+#             */
/*   Updated: 2023/01/15 12:15:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int result;
	
	if (ac == 4)
	{
		if (av[2][0] == '*')
			result = atoi(av[1]) * atoi(av[3]);
		if (av[2][0] == '+')
			result = atoi(av[1]) + atoi(av[3]);
		if (av[2][0] == '-')
			result = atoi(av[1]) - atoi(av[3]);
		if (av[2][0] == '/')
			result = atoi(av[1]) / atoi(av[3]);
		if (av[2][0] == '%')
			result = atoi(av[1]) % atoi(av[3]);
		printf("%d", result);
	}
	printf("\n");
}