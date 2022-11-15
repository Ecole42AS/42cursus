/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphaa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:56:14 by astutz            #+#    #+#             */
/*   Updated: 2022/11/15 13:59:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int intlen(int nb)
{
	int	count;
	
	if (nb <= 0)
		return (NULL);
	while (nb > 0 && nb < 10)
	{
		nb /= 10;
		count++;
	}
	return	(count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;

	str = malloc((intlen(nb) + 1) * sizeof(char));
	if (n <= 0)
		return (NULL);
	i = 0;
	while (n > 0 && n <= 9)
	{
		n = n / 10;
		str[i] = n % 10	+ 48;
		i++;
	}
	return (str);
}