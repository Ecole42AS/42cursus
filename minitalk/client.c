/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:14:42 by astutz            #+#    #+#             */
/*   Updated: 2023/04/25 18:20:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include "minitalk.h"

void	send_bit(int pid, char c)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c >> shift & 1) //entre dans le if, seulement si le bit est 1
		{
			kill(pid, SIGUSR2);
		}
		else
			kill(pid, SIGUSR1);
		shift++;
		usleep(100);
	}
}

void	ft_send_str(int pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (j < 8)
		{
			if (str[i] >> j & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(50);
			j++;
		}
		i++;
	}
	ft_send_str(pid, 0);
}

// void	ft_send_str(int pid, char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		send_bit(pid, str[i]);
// 		i++;
// 	}
// 	send_bit(pid, '\0');
// }

int	main(int argc, char **argv)
{
	int		pid;

	if (argv[1])
	{
		pid = ft_atoi(argv[1]);
		if (!pid)
		{
			ft_printf("Please use the correct PID with only 1 arg behind.\n");
			return (0);
		}
	}
	if (argc == 3)
		ft_send_str(pid, argv[2]);
	else
		ft_printf("\nYOU EITHER LEFT IT BLANK OR ARE DOING MORE THAN 1 WORD\n\n");
	return (0);
}
