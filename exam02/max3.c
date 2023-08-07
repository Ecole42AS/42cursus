/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:54:37 by astutz            #+#    #+#             */
/*   Updated: 2023/01/15 12:00:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		max(int* tab, unsigned int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[0] < tab[i])
			tab[0] = tab[i];
		i++;
	}
	return (tab[0]);
}

int main()
{
	int tab[] = {1, 4, 5, 3, 9, 4};
	int res;

	res = max(tab, 6);
	printf("%d", res);
}