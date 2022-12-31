/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 09:33:14 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 09:37:14 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int     *ft_rrange(int start, int end)
{
	int *ptr;
	size_t size;
	int i;
	int *tmp;

	size = (end - start) + 1;
	if (!size || end < start)
		return (0);
	ptr = (int *)malloc(size * sizeof(int));
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while(start <= end)
	{
		*ptr = end;
		ptr++;
		end--;
	}
	return (tmp);
}

int main()
{
	int *range;
	int i;

	i = 0;
	range = ft_rrange(0, -3);
	while(range[i])
	{
		printf("%d", range[i]);
		i++;
	}
}