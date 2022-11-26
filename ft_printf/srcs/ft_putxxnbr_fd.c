/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxxnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:32:42 by astutz            #+#    #+#             */
/*   Updated: 2022/11/26 10:46:24 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putxxnbr_fd(unsigned int n, int fd)
{
	if (n >= 16)
	{
		ft_putxxnbr_fd((n / 16), 1);
		ft_putxxnbr_fd((n % 16), 1);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
			ft_putchar_fd((n - 10 + 'A'), 1);
	}
}