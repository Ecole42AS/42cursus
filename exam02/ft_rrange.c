/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 09:33:14 by astutz            #+#    #+#             */
/*   Updated: 2023/01/16 20:09:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

// int     *ft_rrange(int start, int end)
// {
// 	int *ptr;
// 	size_t size;
// 	int i;
// 	int *tmp;

// 	if (start > size)
// 		size = (start - end) + 1;
// 	else
// 		size = (end - start) + 1;		
// 	ptr = (int *)malloc(size * sizeof(int));
// 	if (!ptr)
// 		return (NULL);
// 	tmp = ptr;
// 	while(start <= end)
// 	{
// 		*ptr = end;
// 		ptr++;
// 		end--;
// 	}
// 	return (tmp);
// }


int	*ft_rrange(int start, int end)
{
	int		*tab;
	int		i;

	tab = (int *)malloc(sizeof(int) * (start - end) + 1);
	i = 0;
	while (start != end)
	{
		tab[i++] = end;
		end -= (start > end) ? -1 : 1;
	}
	tab[i] = end;
	return (tab);
}

int main()
{
	int *range;
	int i;
	int size;
	int end;
	int start;

	start = 0;
	end = -3;
	if (start > end)
        size = start - end + 1;
    else
        size = end - start + 1;

	i = 0;
	range = ft_rrange(start, end);
	while(i < size)
	{
		printf("%d", range[i]);
		i++;
	}
}