/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:39:45 by astutz            #+#    #+#             */
/*   Updated: 2023/01/01 10:39:19 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

// char *to_lowercase(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] >= 'A' && str[i] <= 'Z')
// 			str[i] += 32;
// 		i++;
// 	}
// 	return (str);
// }

int ft_atoi(char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		n *= 10;
		n = n + *str - '0';
		str++;
	}
	return (n);
}

void ft_printhexa(int nb)
{
	char hexadigits[] = "0123456789abcdef";

	if (nb >= 16)
		ft_printhexa(nb / 16);
	write(1, &hexadigits[nb % 16], 1);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_printhexa(ft_atoi(av[1]));
	}
	write(1, "\n", 1);
}
