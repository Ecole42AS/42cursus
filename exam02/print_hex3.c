/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:57:24 by astutz            #+#    #+#             */
/*   Updated: 2023/01/18 14:33:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_atoi(char *str)
{
	int i;
	int nb;
	
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
}

void print_hex(int nb)
{
	char hexdigits[] = "0123456789abcdef";
	
	if (nb >= 16)
		print_hex(nb / 16);
	write(1, &hexdigits[nb % 16], 1);
}

int main(int ac, char **av)
{
	int i;
	int nb;
	
	i = 0;
	nb = ft_atoi(av[1]);
	if (ac == 2)
		print_hex(nb);
	write(1, "\n", 1);
}