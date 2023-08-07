/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:02:43 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 11:06:48 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	lcm(unsigned int a, unsigned int b)
{
	int n;

	if (a == 0 || b == 0)
		return (0);
	else if (a > b)
		n = a;
	else
		n = b;
	while (1)
	{
		if(n % a == 0 && n % b == 0)
			return (n);
		n++;
	}
}

int main()
{
	unsigned int res;

	res = lcm(8, 6);
	printf("%d", res);
}
