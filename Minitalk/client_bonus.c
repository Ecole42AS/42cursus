/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:14:27 by astutz            #+#    #+#             */
/*   Updated: 2023/05/01 18:46:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include "minitalk_bonus.h"

void	send_bit(int pid, char c)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c >> shift & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		shift++;
		usleep(100);
	}
}

void	ft_send_str(int pid, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		send_bit(pid, str[i]);
		i++;
	}
	send_bit(pid, 0);
}

void	bit_handler(int bit)
{
	if (bit == SIGUSR2)
	{
		ft_printf("Houston, we don't have a problem 🚀.\n");
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	int					pid;
	char				*selfpid;
	struct sigaction	signal;

	if (argc != 3)
		return (ft_printf("Please use the correct PID with 1 arg behind.\n"));
	signal = (struct sigaction){0};
	sigemptyset(&signal.sa_mask);
	sigaddset(&signal.sa_mask, SIGUSR1);
	signal.sa_handler = &bit_handler;
	if (sigaction(SIGUSR2, &signal, NULL) != 0)
		ft_printf("Error SIGUSR2\n");
	pid = ft_atoi(argv[1]);
	selfpid = ft_itoa(getpid());
	if (!pid || !selfpid)
		return (ft_printf("Please use the correct PID with 1 arg behind.\n"));
	ft_send_str(pid, argv[2]);
	ft_send_str(pid, selfpid);
	free(selfpid);
	while (1)
		pause();
	return (0);
}
