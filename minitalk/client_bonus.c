/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:14:27 by astutz            #+#    #+#             */
/*   Updated: 2023/04/22 09:52:29 by astutz           ###   ########.fr       */
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
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		send_bit(pid, str[i]);
		i++;
	}
	send_bit(pid, '\0');
}

void	message_handler()
{
	printf("Everything is alright, Captain!");
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	char	*client_pid;


	// ft_printf("My Client PID is: %d\n", getpid());

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		client_pid = ft_itoa(getpid());
		ft_send_str(pid, client_pid);
		ft_send_str(pid, str);
		free(client_pid);
	}
	else
		ft_printf("\nYOU EITHER LEFT IT BLANK OR ARE DOING MORE THAN 1 WORD\n\n");
	while (1)
	{
		signal(SIGUSR1, message_handler);
		pause();
	}
	return (0);
}
