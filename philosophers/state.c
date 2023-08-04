/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:56:44 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 18:56:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* returns true if the state of the sim is to continue */
int	state(t_config *config)
{
	if (!config->life)
		return (0);
	if ((config->t_die + config->last_bite) < get_time('n'))
	{
		state_update(config, 'L');
		return (0);
	}
	pthread_mutex_lock(config->sim_mutex);
	if (config->sim_state[0] == 0)
	{
		pthread_mutex_unlock(config->sim_mutex);
		config->life = 0;
		return (0);
	}
	pthread_mutex_unlock(config->sim_mutex);
	return (1);
}
