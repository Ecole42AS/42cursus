/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:32:56 by astutz            #+#    #+#             */
/*   Updated: 2023/01/12 14:12:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rev_wstr(char *str)
{
	int i;
	int end;
	int start;
	int flag;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		while (str[i] == '\0' || str[i] == '\t' || str[i] == ' ')
			i--;
		end = i;
		while (str[i] && str[i] != '\t' && str[i] != ' ')
			i--; //i = 0 quand on arrive au debut de la string
		start = i + 1;
		flag = start;
		while (start <= end)
			write(1, &str[start++], 1);
		if (flag)
			write(1, " ", 1);
	}
}

int main(int ac, char **av)
{
	if (ac > 1)
		rev_wstr(av[1]);
	write(1, "\n", 1);
}