/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxxnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:32:42 by astutz            #+#    #+#             */
/*   Updated: 2022/11/27 10:14:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	hexalen(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_putxxnbr(unsigned int nb)
{
	unsigned int	len;

	len = hexalen(nb);
	if (nb >= 16)
	{
		ft_putxxnbr((nb / 16));
		ft_putxxnbr((nb % 16));
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + '0'), 1);
		else
			ft_putchar_fd((nb - 10 + 'A'), 1);
	}
	return (len);
}
