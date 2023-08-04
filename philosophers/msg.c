/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:56:05 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 19:08:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg(t_config *config, int status)
{
	static int	lol;

	if (status == EATS && lol < 1 && state(config))
		printf("%d %d is eating\n", get_time('n'), config->pos + 1);
	else if (status == SLEEPS && lol < 1 && state(config))
		printf("%d %d is sleeping\n", get_time('n'), config->pos + 1);
	else if (status == THINKS && lol < 1 && state(config))
		printf("%d %d is thinking\n", get_time('n'), config->pos + 1);
	else if (status == DIES && ++lol < 2) //datarace
		printf("%d %d died\n", get_time('n'), config->pos + 1);
	else if (status == FORKS && lol < 1 && state(config))
		printf("%d %d has taken a fork\n", get_time('n'), config->pos + 1);
}
