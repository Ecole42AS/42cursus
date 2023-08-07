/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:04:15 by astutz            #+#    #+#             */
/*   Updated: 2022/12/20 20:50:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void repeat_alpha(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	while(str[i])
	{
		if(str[i] >= 'a' && str[i] <= 'z')
		{
			j = 0;
			while(j < str[i] - 96)
			{
				write(1, &str[i], 1);
				j++;
			}
		}
		else if(str[i] >= 'A' && str[i] <= 'Z')
		{
			k = 0;
			while(k < str[i] - 64)
			{
				write(1, &str[i], 1);
				k++;
			}
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if(ac == 2)
	{
		repeat_alpha(av[1]);
	}
	write(1, "\n", 1);
}
