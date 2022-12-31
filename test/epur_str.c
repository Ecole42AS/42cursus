/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:58:20 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 08:20:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_epur_str(char *str)
{
	int flag;
	int i;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			flag = 1;
		if(!(str[i] == ' ' || str[i] == '\t'))
		{
			if(flag)
				write(1, " ", 1);
			flag = 0;
			write(1, &str[i], 1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if(ac == 2)
	{
		ft_epur_str(av[1]);
	}
	write(1, "\n", 1);
}