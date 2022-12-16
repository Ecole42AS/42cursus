/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:32:12 by astutz            #+#    #+#             */
/*   Updated: 2022/12/16 16:02:09 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int max( int *tab, unsigned int len)
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

	res = max(numbers, 5);
	printf("%d", res);
}

