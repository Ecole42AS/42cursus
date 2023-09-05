/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:21:16 by astutz            #+#    #+#             */
/*   Updated: 2023/09/05 21:19:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void put_string(char *str, int *len)
{
	if (!str)
		write(1, "(null)", 6);
	while(*str)
		*len += write(1, str++, 1);
}

void put_number_base(long long int nb, int base, int *len)
{
	char *hexadecimal;
	
	hexadecimal = "0123456789abcdef";
	if (nb < 0)
	{
		nb *= -1;
		*len += write(1, "-", 1);
	}
	if (nb >= base)
		put_number_base((nb / base), base, len);
	*len += write(1, &hexadecimal[nb % base], 1);
}

int	ft_printf(const char * restrict format, ...)
{
	int i;
	va_list ap;
	int len;

	i = 0;
	va_start(ap, format);
	while(format[i])
	{
		if (((format[i] == '%') && (format[i + 1] == 's')) 
		|| ((format[i] == '%') && (format[i + 1] == 'd')) 
		|| ((format[i] == '%') && (format[i + 1] == 'x')))
		{
			i++;
			if (format[i] == 's')
				put_string((va_arg(ap, char *)), &len);
			else if (format[i] == 'd')
				put_number_base(((long long int)va_arg(ap, int)), 10, &len);
			else if (format[i] == 'x')
				put_number_base(((long long int)va_arg(ap, unsigned int)), 16, &len);
		} else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return(len);
}

int main() {
    printf("=== Testing ft_printf ===\n");

    // Test with strings and integers
    ft_printf("Hello, %s!\n", "world");
    ft_printf("The answer is %d.\n", -42);

    // Test with hexadecimal integers
    ft_printf("Hexadecimal: %x\n", -777);
    ft_printf("Hexadecimal: %x\n", 0x1000);

    return 0;
}
