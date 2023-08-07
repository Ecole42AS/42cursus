/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:13:29 by astutz            #+#    #+#             */
/*   Updated: 2023/07/30 18:44:32 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	intlen(unsigned int nb)
// {
// 	int	len;

// 	len = 0;
// 	if (nb == 0)
// 		return (1);
// 	if (nb != 0)
// 	{
// 		nb /= 10;
// 		len++;
// 	}
// 	return (len);
// }

// int	ft_putunbr(unsigned int nb)
// {
// 	int	len;

// 	len = intlen(nb);
// 	if (nb > 9)
// 	{
// 		ft_putunbr(nb / 10);
// 	}
// 	ft_putchar_fd((nb % 10 + '0'), 1);
// 	return (len);
// }

static int	sizemalloc(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static char	*uitoa(unsigned int n)
{
	char	*ptr;
	int		i;

	i = sizemalloc(n);
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == 0)
		return (NULL);
	ptr[i] = '\0';
	if (n == 0)
		ptr[0] = 48;
	while (n != '\0')
	{
		ptr[i - 1] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (ptr);
}

int	ft_putunbr(unsigned int nb)
{
	char	*str;
	int		len;

	str = uitoa(nb);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free (str);
	return (len);
}
