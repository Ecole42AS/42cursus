/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 09:40:31 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 10:01:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void hidenp(char *str, char *str1)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && str1[j])
	{
		if (str[i] == str1[j])
			i++;
		j++;
	}
	if (str[i] == '\0')
		write(1, "1", 1);
	else
		write(1, "0", 1);
}

int main(int ac, char **av)
{
	
	if (ac == 3)
	{
		hidenp(av[1], av[2]);
	}
	write(1, "\n", 1);
}