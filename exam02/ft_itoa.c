/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:47:47 by astutz            #+#    #+#             */
/*   Updated: 2023/01/03 14:17:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// int			ft_intlen(int n)
// {
// 	int				idx;
// 	long long		tmp;

// 	tmp = n;
// 	idx = 1;
// 	if (tmp < 0)
// 	{
// 		tmp = tmp * -1;
// 		idx++;
// 	}
// 	while (tmp >= 10)
// 	{
// 		tmp = tmp / 10;
// 		idx++;
// 	}
// 	return (idx);
// }

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

char	*ft_itoa(int n)
{
	char *str;
	int size;
	int i;
	long long nb;

	i = 0;
	nb = n;
	size = intlen(nb);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (nb == 0)
	{
		str[0]= '0';
		i++;
	}
	if (nb < 0)
	{
		str[0]= '-';
		nb = -nb;
		i++;
	}
	while (nb > 0 && size > 0)
	{
		str[size - 1] = (nb % 10) + 48;
		nb /= 10;
		size--;
	}
	return (str);
}

// char    *ft_itoa(int nbr)
// {
// 	int	len;
// 	long	n_tmp;
// 	char	*str;

// 	len = 0;
// 	n_tmp = nbr;
// 	str[len] ='\0';
	
// 	if (nbr == -2147483648)
// 		return ("-2147483648");
// 	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
// 		return (NULL);
// 	if (nbr == 0)
// 	{
// 		str[0] = '0';
// 		return (str);
// 	}
// 	if (nbr < 0)
// 	{
// 		len += 1;
// 		nbr *= -1;
// 		str[0] = '-';
// 	}
// 	while (n_tmp)
// 	{
// 		n_tmp /= 10;
// 		len += 1;
// 	}
// 	while (nbr)
// 	{
// 		str[--len] = (nbr % 10) + '0';
// 		nbr /= 10;
// 	}
// 	return (str);
// }

int main()
{
	int len;
	char *str;
	
	str = ft_itoa(2147483647);
	// len = intlen(-2345);
	// printf("%d", len);
	printf("%s", str);
}