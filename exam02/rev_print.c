/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:22:07 by astutz            #+#    #+#             */
/*   Updated: 2022/12/10 08:35:42 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int main(int ac, char **av)
{
	char	*str;
	int		i;
	
	str = av[1];
	i = ft_strlen(str);
	if (ac == 2)
	{
		while(i)
			write(1, &str[--i], 1);
	}
	write(1, "\n", 1);
	return (0);
}