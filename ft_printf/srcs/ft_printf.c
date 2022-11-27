/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:25:59 by astutz            #+#    #+#             */
/*   Updated: 2022/11/27 09:23:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	formating(char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_print_c(va_arg(ap, int));
	else if (c == 's')
		ft_print_s(va_arg(ap, char *));
	else if (c == 'p')
		ft_putptr(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		len += ft_print_di(va_arg(ap, int));
	else if (c == 'u')
		len += ft_putunbr(va_arg(ap, unsigned int));
	else if (c == 'x')
		ft_putxnbr(va_arg(ap, int));
	else if (c == 'X')
		ft_putxxnbr(va_arg(ap, int));
	else if (c == '%')
		ft_print_percent();
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			len += formating(format[++i], ap);
		else
			len += ft_print_c(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}

// int main()
// {
// 	//printf("test c: %c \n test s: 1) %s\t2) %s\n.",
// 'Z', "test1", "test2");
// 	ft_printf("\n\ntest c: %c \ntest s: 1) %s\t2) %s \ntest
// p : %p\ntest d: %d \ntest i: 1) %i\t 2) %i\ntest u: 1)%u\t
// 2) %u\ntest x: %x\ntest X: %X\ntest pourcent: %%\n.", 'Z',
// "test1", "test2", "TESTP", 12345, 213, -9876543, 4294967292,
// 3294967292, 198, 198);
// }