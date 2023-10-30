/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2023/10/02 17:42:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../minishell.h"

void	prnt(int i, char **argv)
{
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (!argv[i])
			break ;
		write(1, " ", 1);
	}
}

void	echo(char **argv)
{
	if (argv[1] == NULL)
		write(1, "\n", 1);
	else if (!ft_strncmp(argv[1], "-n", 3))
		prnt(2, argv);
	else
	{
		prnt(1, argv);
		write(1, "\n", 1);
	}
}
