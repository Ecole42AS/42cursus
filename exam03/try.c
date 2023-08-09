/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:02:04 by astutz            #+#    #+#             */
/*   Updated: 2023/08/08 14:27:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void put_string(char *str, int *len)
{
	if(!str)
		str = "(null)";
	while(*str)
		*len += write(1, str++, 1);
}

void put_digit(long long int nb, int base, int *len)
{
	char *hexadecimal = "0123456789abcdef";

	if(nb < 0)
	{
		nb *= -1;
		*len += write(1, "-", 1);
	}
	if(nb >= base)
		put_digit((nb/base), base, len);
	*len += write(1, &hexadecimal[nb % base], 1);
}

int ft_printf(const char *format, ...)
{
	int len = 0;
	
	va_list ptr;
	va_start(ptr, format);
	
	while(*format)
	{
		if ((*format == '%' && *(format + 1) == 's')
		|| (*format == '%' && *(format + 1) == 'd') 
		|| (*format == '%' && *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(ptr, char*), &len);//à revoir format si besoin de dereferencer)
			if (*format == 'd') //peut etre mettre elseif
				put_digit((long long int)va_arg(ptr, int), 10, &len);//à revoir format si besoin de dereferencer)
			if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);//à revoir ++format si besoin de dereferencer)
		}
		else
			len += write(1, format, 1);
		*format++;
	}
	
	return (va_end(ptr), len);
}

int main()
{
    printf("=== Testing ft_printf ===\n");

    // Test avec des chaînes et des entiers
    ft_printf("Hello, %s!\n");
    ft_printf("The answer is %d.\n", -42);

    // Test avec des entiers hexadécimaux
    ft_printf("Hexadecimal: %x\n", -777);
    ft_printf("Hexadecimal: %x\n", 0x1000);

    return 0;
}
