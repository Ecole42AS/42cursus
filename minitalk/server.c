/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:06 by astutz            #+#    #+#             */
/*   Updated: 2023/04/25 18:19:05 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/includes/ft_printf.h"

int	ft_recursive_power(int nb, int power) //si on utilise nb = 2 et power = 3
{
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1)); //2 * (2 * (2 * 1))
}

char	*char_join(char *str, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
	if (ptr == 0)
		return (NULL);
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = c;
	i++;
	ptr[i] = '\0';
	free(str);
	return (ptr);
}

void	bit_handler(int bit)
{
	static t_msg	g_msg = {0};

	if (!g_msg.str)
	{
		g_msg.str = malloc(sizeof(char) * 1);
		g_msg.str[0] = 0;
	}
	// 10100110
	//1 * 2^7 + 0 * 2^6 + 1 * 2^5 + 0 * 2^4 + 0 * 2^3 + 1 * 2^2 + 1 * 2^1 + 0 * 2^0
	if (bit == SIGUSR2) //bit = 1
		g_msg.str += ft_recursive_power(2, g_msg.i);
	if (++g_msg.i == 8)// ou == 7 en enlevant le ++
	{
		if (g_msg.c == 0)
		{
			ft_printf("%s\n", g_msg.str);
			free(g_msg.str);
			g_msg.str = NULL;
		}
		else
			g_msg.str = char_join(g_msg.str, g_msg.c);
		g_msg.i = 0;
		g_msg.c = 0;
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
