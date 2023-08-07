/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:34:29 by astutz            #+#    #+#             */
/*   Updated: 2023/01/16 20:15:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
// #include <stdio.h>

int	*ft_range(int start, int end)
{
	int	*res;
	int	size;
	int	i;

	size = (end - start) + 1;
	i = 0;
	res = (int *) malloc(size * sizeof(int));
	if (!res)
		return (NULL);
	while (i++ < size)
		res[i] = start + i;
	return (res);
}

/*
int main(void)
{
	int	start;
	int	end;
	int	i;
	int	*tab;
	start = 0;
	end = 0;
	tab = ft_range(start, end);
	i = 0;
	while (i < (end - start) + 1)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}
*/