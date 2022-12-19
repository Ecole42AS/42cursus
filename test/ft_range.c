/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:34:29 by astutz            #+#    #+#             */
/*   Updated: 2022/12/19 18:38:08 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>

int *ft_range(int start, int end)
{
	int size = end - start;
	int *ret;
	int *pointer;

	if (size)
	{
		pointer = (int *)malloc(sizeof(int) * size);
		if (pointer)
		{
			ret = pointer;
			while (start <= end)
			{
				*pointer = start;
				pointer++;
				start++;
			}
			return (ret);
		}
	}
	return (NULL);
}

int main()
{
	int *range;
	int i;
	
	i = 0;
	range = ft_range(2, 5);
	while (range[i])
		printf("%d", range[i++]);
}