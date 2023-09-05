/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:59:05 by astutz            #+#    #+#             */
/*   Updated: 2023/08/21 20:49:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

void to_string(char *str, int len)
{
	if (!str)
		return ("null");
	while (*str)
	{
		len += (1, &str, 1);
		*str++;
	}
}

int printf(const char *format, ...)
{
	int i;
	va_list ap;
	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if(format[i] == '%' && format[i + 1] == 's')
			to_string(va_arg(ap, char *));
	}
	va_end
	return (len)
}