/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:52:38 by astutz            #+#    #+#             */
/*   Updated: 2023/01/07 10:46:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// int main(int argc, char **argv)
// {
// 	int i = 0;
// 	int start;
// 	int end;
// 	int flag = 0;
	
// 	if (argc > 1)
// 	{
// 		while(argv[1][i] == ' ' || argv[1][i] == '\t')
// 			i++;
// 		start = i;
// 		while(argv[1][i] && (argv[1][i] != ' ' &&  argv[1][i] != '\t'))
// 			i++;
// 		end = i;
// 		while(argv[1][i] == ' ' || argv[1][i] == '\t')
// 			i++;
// 		while(argv[1][i] != '\0')
// 		{
// 			flag = 1;
// 			write (1, &argv[1][i], 1);
// 			i++;				
// 		}
// 		if (flag == 1)
// 		{
// 			write (1, " ", 1);
// 		}
// 		while(start < end)
// 		{
// 			write (1, &argv[1][start], 1);
// 			start++;
// 		}
// 	}	
// 	write (1, "\n",1);	
// }

void rostring(char *str)
{
	int i;
	int flag;
	int flag2;
	int start;
	int end;

	flag = 0;
	flag2 = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	start = i;
	while (str[i] && (str[i] != '\t' && str[i] != ' '))
		i++;
	end = i - 1;
	printf("%c\n --------\n", str[end]);
	printf("%d\n --------\n", end);
	while (str[i] == '\t' || str[i] == ' ')
	i++;
	while (str[i])
	{
		flag2 = 1;
		if (str[i] == ' ' || str[i] == '\t')
			flag = 1;
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			if (flag)
				write(1, " ", 1);
			flag = 0;
			write(1, &str[i], 1);
		}
		i++;
	}
	if (flag2)
		write(1, " ", 1);
	while (start <= end)
		write(1, &str[start++], 1);
}

int main(int ac, char **av)
{
	if (ac > 1)
		rostring(av[1]);
	write(1, "\n", 1);
}