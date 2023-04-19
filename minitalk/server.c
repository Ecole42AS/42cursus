/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:06 by astutz            #+#    #+#             */
/*   Updated: 2023/04/19 21:30:52 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/includes/ft_printf.h"

void	bit_handler(int bit)
{
	// printf("bit_handler called with bit: %d\n", bit);
	g_msg.c += ((bit & 1) << g_msg.i);
	g_msg.i++;
	if (g_msg.i == 7)
	{
		// printf("bit_handler received character: %c\n", g_msg.c);
		ft_printf("%c", g_msg.c);
		if (!g_msg.c)
			ft_printf("\n");
		g_msg.c = 0;
		g_msg.i = 0;
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