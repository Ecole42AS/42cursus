/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:05:05 by astutz            #+#    #+#             */
/*   Updated: 2023/01/18 13:32:00 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putnbr(int nb)
{
	char digit;
	if (nb > 9)
	
		ft_putnbr(nb / 10);
	digit = (nb % 10) + 48;
	write(1, &digit, 1);	
}

// int main(int ac, char **av)
// {
// 	char nb_of_params;
	
// 	if (ac <= 1)
// 		write(1, "0", 1);
// 	nb_of_params = (ac - 1) + '0';
// 	if (ac > 1)
// 	{
// 		write(1, &nb_of_params, 1);
// 	}
// 	write(1, "\n", 1);
// }

int main(int ac, char **av)
{
	(void)av;
	
	ft_putnbr(ac - 1);
	write(1, "\n", 1);
	return (0);
}