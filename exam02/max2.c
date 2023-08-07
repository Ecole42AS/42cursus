/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:56:35 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 14:10:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		max2(int* tab, unsigned int len)
{
	int result;
	int i;

	result = tab[0];
	i = 0;
	while(i < len)
	{
		if(tab[i] >= result)
			result = tab[i];
		i++;
	}
	return (result);
}

int max(int *tab, unsigned int len)
{
	int result;
	int i = 0;
	result = tab[i];
	
	while(i < len)
	{
		if (result < tab[i])
		{
			result = tab[i];
		}
		i++;
	}
	return result;
}

int main()
{
	int numbers[] = {3, 4, 2, 5, 1};
	int res;
	int res1;

	res = max2(numbers, 6);
	res1 = max(numbers, 6);
	printf("%d\n", res);
	printf("%d", res1);
}
