/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:21:27 by astutz            #+#    #+#             */
/*   Updated: 2023/04/22 10:26:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "ft_printf/includes/ft_printf.h"

void	bit_handler(int bit)
{
	static t_msg	g_msg = {0};

	if (!g_msg.client_pid)
		g_msg.client_pid = bit;
	else
	{
		g_msg.c += ((bit & 1) << g_msg.i);
		g_msg.i++;
		if (g_msg.i == 8)
		{
			ft_printf("%c", g_msg.c);
			if (!g_msg.c)
				g_msg.msg_received = 1;
			g_msg.c = 0;
			g_msg.i = 0;
		}		
	}
	if (g_msg.msg_received)
	{
		kill(g_msg.client_pid, SIGUSR1);
	}
}

int	main(void)
{
	ft_printf("Welcome To Alex's Server!\n");
	ft_printf("My Server PID is: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR2, bit_handler);
		signal(SIGUSR1, bit_handler);
		pause();
	}
	return (0);
}
