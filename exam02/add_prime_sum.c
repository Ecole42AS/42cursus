/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:16:18 by astutz            #+#    #+#             */
/*   Updated: 2022/12/28 21:49:27 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void ft_putnbr(int nb)
{
	if(nb == INT_MIN)
		write(1,"-2147483648", 11);
	else if(nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		ft_putnbr(nb);
	}
	else if(nb < 10)
	{
		nb = nb + 48;
		write(1, &nb, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
		nb = (nb % 10) + 48;
		write(1, &nb, 1);
	}
}

int ft_is_prime(int nb)
{
	int i;

	i = 3;
	if(nb % 2 == 0 && nb > 2)
		return (0);
	while(i < (nb / 2))
	{
		if (nb % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int add_prime_sum(int nb)
{
	int result;

	while(nb > 0)
	{
		if(ft_is_prime(nb) == 1)
			result += nb;
		nb--;
	}
	return (result);
}

int main(int ac, char **av)
{
	int result;
	int nb = atoi(av[1]);
	result = 0;
	if(ac == 2)
	{
		result = add_prime_sum(nb);
		ft_putnbr(result);
	}
	else
		ft_putnbr(0);
	write(1, "\n", 1);
}

// int main()
// {
// 	printf("%d", INT_MIN);
// }