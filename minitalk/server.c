/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:16:06 by astutz            #+#    #+#             */
/*   Updated: 2023/04/24 14:57:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/includes/ft_printf.h"

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
	int	i;

	i = 0;
	g_msg.c += ((bit & 1) << g_msg.i);
	g_msg.i++;
	if (!g_msg.str)
	{
		g_msg.str = malloc(sizeof(char) * 1);
		g_msg.str[0] = 0;
	}
	if (g_msg.i == 8)
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
