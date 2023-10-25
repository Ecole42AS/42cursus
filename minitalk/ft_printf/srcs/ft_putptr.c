/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:37:20 by astutz            #+#    #+#             */
/*   Updated: 2022/11/27 09:24:23 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_countn_px(unsigned long nb)
{
	unsigned long	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != '\0')
	{
		nb /= 16;
		i++;
	}
	return (i);
}

static int	ft_print_px(unsigned long nb)
{
	unsigned long	len;

	len = 0;
	if (nb >= 16)
	{
		ft_print_px(nb / 16);
		ft_print_px(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + '0'), 1);
		else
			ft_putchar_fd((nb - 10 + 'a'), 1);
	}
	len = ft_countn_px(nb);
	return (len);
}

int	ft_putptr(unsigned long nb)
{
	unsigned long	len;

	len = 0;
	write(1, "0x", 2);
	len += ft_print_px(nb);
	return (len + 2);
}
