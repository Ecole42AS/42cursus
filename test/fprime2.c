/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:21:05 by astutz            #+#    #+#             */
/*   Updated: 2023/01/16 19:27:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int ft_isprime(int nb)
{
	int i;

	i = 3;
	if (nb <= 1)
		return(0);
	if (nb % 2 == 0 && nb > 2)
		return (0);
	while (i < (nb / 2))
	{
		if (nb % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

// int main(int ac, char **av)
// {
// 	int nb;
// 	int i;

// 	i = 0;
// 	nb = atoi(av[1]);
// 	if (ac == 2)
// 	{
// 		while (i <= nb)
// 		{
// 			if (ft_isprime(nb) == 1)
// 			{
// 				printf("%d", nb);
// 				printf("*");
// 			}
// 			i++;
// 		}
// 	}
// 	printf("\n");
// }

void	ft_putnb(int n, in)
{
	if (n == -2147483648)
	{
		ft_putcha('-');
		ft_putcha('2');
		ft_putnb(147483648);
	}
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * -1);
	}
	else if (n < 10)
		ft_putcha((char)(n + '0'));
	else
	{
		ft_putnb(n / 10);
		ft_putcha(n % 10 + '0');
	}
}

int main(int argc, char *argv[])
{
	int sum = 0;
	int nb = atoi(argv[1]);
	
	if (argc == 2)
	{
		while (nb > 0)
			if (ft_isprime(nb--))
				sum += (nb + 1);
		ft_putnbr_fd(sum, 1);
	}
	if (argc != 2)
		ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	return (0);
}