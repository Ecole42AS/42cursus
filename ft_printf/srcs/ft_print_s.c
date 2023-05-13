/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:43:48 by astutz            #+#    #+#             */
/*   Updated: 2023/05/13 12:26:26 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_s(char *str)
{
	int	n;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(str, 1);
	n = ft_strlen(str);
	return (n);
}
