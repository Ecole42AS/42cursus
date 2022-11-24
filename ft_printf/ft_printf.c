/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:25:59 by astutz            #+#    #+#             */
<<<<<<< HEAD:ft_printf/srcs/ft_printf.c
/*   Updated: 2022/11/24 19:38:33 by astutz           ###   ########.fr       */
=======
/*   Updated: 2022/11/24 15:23:08 by astutz           ###   ########.fr       */
>>>>>>> bd7d3a046563a0a209a703d9b7f8ef7c631e28af:ft_printf/ft_printf.c
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int	formating(char c, va_list ap)
{
	int n;
	
	if (c == 'c')
		n = 1;
	else if (c == 's')
		return (ft_strlen(ap))
		ft_putstr_fd(va_arg(ap, char *), 1);
	// else if (c == 'p')
	// 	ft_putptr_fd(va_arg(ap, void *), 1);
	// else if (c == 'd' || c == 'i')
	// 	ft_putnbr_fd(va_arg(ap, int), 1);
	// else if (c == 'i')
	// 	ft_putnbr_fd(va_arg(ap, int), 1);
	// else if (c == 'u')
	// 	ft_putunbr_fd(va_arg(ap, unsigned int), 1);
	// else if (c == 'x')
	// 	ft_putxnbr_fd(va_arg(ap, int), 1, 0);
	// else if (c == 'X')
	// 	ft_putxnbr_fd(va_arg(ap, int), 1, 1);
	else if (c == '%')
		ft_putchar_fd('%', 1);
	else
		return (0);
	return (n);
}

int	ft_printf(const char *format, ...)
{
<<<<<<< HEAD:ft_printf/srcs/ft_printf.c
	//int		param_nbr;
=======
	// int		param_nbr;
>>>>>>> bd7d3a046563a0a209a703d9b7f8ef7c631e28af:ft_printf/ft_printf.c
	int		i;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			formating(format[++i], ap);
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
