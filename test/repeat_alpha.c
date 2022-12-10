/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:39:42 by astutz            #+#    #+#             */
/*   Updated: 2022/12/09 21:25:04 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	ft_repeat_alpha(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			j = str[i] - 65;
			while (j >= 0)
			{
				ft_putchar(str[i]);
				j--;
			}
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			j = str[i] - 97;
			while (j >= 0)
			{
				ft_putchar(str[i]);
				j--;
			}
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
	return (*str);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_repeat_alpha(argv[1]);
	}
	else
	{
		ft_putchar('\n');
	}
	return (0);
}

// void	repeat_alpha(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] >= 'a' && str[i] <= 'z')
// 		{
// 			j = str[i] - 97;
// 			while (j >= 0)
// 			{
// 				write(1, &str[i], 1);
// 				j--;
// 			}
// 		}
// 		j = 0;
// 		if (str[i] >= 'A' && str[i] <= 'Z')
// 			j = str[i] - 65;
// 		while (j >= 0)
// 		{
// 			write(1, &str[i], 1);
// 			j--;
// 		}
// 		i++;
// 	}
// }

// int main(int ac, char **av)
// {
// 	if(ac == 2)
// 	{
// 		repeat_alpha(av[1]);
// 	}
// 	write(1, "\n", 1);
// }
