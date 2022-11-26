/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:13:29 by astutz            #+#    #+#             */
/*   Updated: 2022/11/26 20:15:41 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	intlen(unsigned int nb)
{
	int	len;

	len = 0;
	if(nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);	
}

void	ft_putunbr_fd(unsigned int nb)
{
	int len;

	len = intlen(nb);
	if (nb > 9)
	{
		ft_putunbr_fd(nb / 10, fd);
	}
	ft_putchar_fd((nb % 10 + '0'), fd);
	return (len);
}
