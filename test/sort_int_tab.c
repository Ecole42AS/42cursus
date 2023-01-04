/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:23:10 by astutz            #+#    #+#             */
/*   Updated: 2023/01/04 20:46:00 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
// void	sort_int_tab(int *tab, unsigned int size)
// {
// 	unsigned int	i = 0;
// 	int	temp;

// 	while (i < (size - 1))
// 	{
// 		if (tab[i] > tab[i + 1])
// 		{
// 			temp = tab[i];
// 			tab[i] = tab[i+ 1];
// 			tab[i + 1] = temp;
// 			i = 0;
// 		}
// 		else
// 			i++;
// 	}
// }
void sort_int_tab(int *tab, unsigned int size)
{
	int i;
	int tmp;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

int main()
{
	int tab[] = {3, 5, 6, 2, 6, 8, 1};
	int i;
	int length = sizeof(tab)/sizeof(tab[0]);    
	printf("%d\n", length);


	i = 0;
	sort_int_tab(tab, 7);
	while (i < length)
	{
		printf("%d", tab[i]);
		i++;
	}
}