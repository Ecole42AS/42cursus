/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 08:38:22 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 09:33:24 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*range;
	int	size;
	int	i;

	range = NULL;
	if (min >= max)
		return (range);
	size = (max - min) + 1;
	i = 0;
	range = (int *) malloc((size + 1) * sizeof(int));
	while (i <= size)
	{
		range[i] = min + i;
		i++;
	}
	return (range);
}

// int     *ft_range(int start, int end)
// {
// 	int *ptr;
// 	size_t size;
// 	int i;
// 	int *tmp;

// 	size = (end - start) + 1;
// 	if (!size)
// 		return (0);
// 	ptr = (int *)malloc(size * sizeof(int));
// 	if (!ptr)
// 		return (NULL);
// 	tmp = ptr;
// 	while(start <= end)
// 	{
// 		*ptr = start;
// 		ptr++;
// 		start++;
// 	}
// 	return (tmp);
// }

int main()
{
	int *range;
	int i;

	i = 0;
	range = ft_range(-1, 5);
	while(range[i])
	{
		printf("%d", range[i]);
		i++;
	}
}