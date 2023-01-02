/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:47:47 by astutz            #+#    #+#             */
/*   Updated: 2023/01/02 16:33:40 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int			ft_intlen(int n)
{
	int				idx;
	long long		tmp;

	tmp = n;
	idx = 1;
	if (tmp < 0)
	{
		tmp = tmp * -1;
		idx++;
	}
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		idx++;
	}
	return (idx);
}

int intlen(int n)
{
	int len;
	long long nb;
	
	nb = n;
	len = 0;
	if (nb <= 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	
}

int main()
{
	int len;
	
	len = intlen(-2345);
	printf("%d", len);
}