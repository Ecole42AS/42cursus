/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:31:00 by astutz            #+#    #+#             */
/*   Updated: 2022/12/20 19:59:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *search_and_replace(char *str, char *c, char *r)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(ft_strlen(c) == 1 && ft_strlen(r) == 1)
		{
			if(str[i] == c[0])
				str[i] = r[0];
		}
		write (1, &str[i], 1);
		i++;
	}
	return (str);
}

int main(int ac, char **av)
{
	if (ac == 4)
	{
		search_and_replace(av[1], av[2], av[3]);
	}
	write(1, "\n", 1);
}