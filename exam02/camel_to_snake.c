/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:14:30 by astutz            #+#    #+#             */
/*   Updated: 2022/12/10 09:40:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>

// void camel_to_snake(char *str)
// {
// 	int majcount;
// 	int i;
	
// 	i = 0;
// 	majcount = 0;
// 	while(str[i])
// 	{
// 		if(str[i] >= 65 && str[i] <= 90)
// 			str[i - 1] = "_"; 
// 			majcount++;
		
// 	}
// }

#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;

	if (argc == 2)
	{
		while(argv[1][i])
		{
			if(argv[1][i] >= 65 && argv[1][i] <= 90)
			{
				argv[1][i] = argv[1][i] + 32;
				write (1, "_", 1);
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
}
