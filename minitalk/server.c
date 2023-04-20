/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:06 by astutz            #+#    #+#             */
/*   Updated: 2023/04/20 14:53:50 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/includes/ft_printf.h"

void	bit_handler(int bit)
{
	static t_msg g_msg = {0};
	// printf("bit_handler called with bit: %d\n", bit);
	g_msg.c += ((bit & 1) << g_msg.i);
	// printf("Value of g_msg.c is %d\n", g_msg.c);
	g_msg.i++;
	if (g_msg.i == 8)
	{
		// printf("bit_handler received character: %c\n", g_msg.c);
		ft_printf("%c", g_msg.c);
		if (!g_msg.c)
			ft_printf("\n");
		g_msg.c = 0;
		g_msg.i = 0;
	}
	// if (g_msg.c == '\0')
	// {
	// 	kill(pid, SIGUSR1);
	// }
	
}
// quand le serveur recoit '/0', il doit envoyer un signal au client et lorsque le client recoit ce message, 
//il doit afficher un message comme quoi le message a bien ete transmis au serveur.
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