/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:25:59 by astutz            #+#    #+#             */
/*   Updated: 2022/11/24 14:24:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	formating(char c, va_list ap)
{
	if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	else if (c == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	else if (c == 'p')
		ft_putptr_fd(va_arg(ap, void *), 1);
	else if (c == 'd')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (c == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (c == 'u')
		ft_putunbr_fd(va_arg(ap, unsigned int), 1);
	else if (c == 'x')
		ft_putxnbr_fd(va_arg(ap, int), 1, 0);
	else if (c == 'X')
		ft_putxnbr_fd(va_arg(ap, int), 1, 1);
	else if (c == '%')
		ft_putchar_fd('%', 1);
}

int	ft_printf(const char *format, ...)
{
	// int		param_nbr;
	int		i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			formating(format[++i], ap);
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (1);
}

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	ft_printf("\ntest c: %c \ntest s: 1) %s\t2) %s \ntest$ p : %p\ntest d: %d \ntest i: 1) %i\t 2) %i\ntest u: 1)%u\t 2) %u\ntest x: %x\ntest X: %X\ntest pourcent: %%\n.", 'Z', "test1", "test2", "TESTP", 12345, 213, -9876543, 4294967292, 3294967292, 198, 198);
}
