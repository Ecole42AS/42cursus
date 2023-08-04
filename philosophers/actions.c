/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:55:01 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 18:55:11 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo(t_config *config);

/* philosopher is eating */
void	eats(t_config *config)
{
	int	start;

	if (!state(config))
		return ;
	while (config->life && pthread_mutex_lock(&config->forks[config->pos]))
		state(config);
	msg(config, FORKS);
	if (config->nb_philo == 1)
		solo(config);
	if (!config->life)
		return ;
	while (config->life && pthread_mutex_lock(&config->forks[config->next_pos]))
		state(config);
	msg(config, FORKS);
	start = get_time('n');
	msg(config, EATS);
	config->last_bite = get_time('n');
	while (config->life && (start + config->t_eat) > get_time('n'))
		state(config);
	pthread_mutex_unlock(&config->forks[config->pos]);
	pthread_mutex_unlock(&config->forks[config->next_pos]);
	if (config->life && config->nb_t_eat >= 0 \
	&& (++config->ate == config->nb_t_eat))
		state_update(config, 'E');
}

/* philosopher is sleeping */
void	sleeps(t_config *config)
{
	int	start;

	state(config);
	if (!config->life)
		return ;
	start = get_time('n');
	msg(config, SLEEPS);
	while (config->life && (start + config->t_sleep) > get_time('n'))
		state(config);
}

/* philosopher is thinking */
void	thinks(t_config *config)
{
	state(config);
	if (!config->life)
		return ;
	msg(config, THINKS);
}

/* updates the sim_state variable based on the flag
	if flag == 'L', put sim_state[0] == 0
	if flag == 'E', increases sim_state[1]++
	and check if the philos have all eaten */
void	state_update(t_config *config, char flag)
{
	if (flag == 'L')
	{
		pthread_mutex_lock(&config->sim_mutex[0]);
		config->sim_state[0] = 0;
		pthread_mutex_unlock(&config->sim_mutex[0]);
		config->life = 0;
		msg(config, DIES);
		return ;
	}
	if (flag == 'E')
	{
		pthread_mutex_lock(&config->sim_mutex[1]);
		config->sim_state[1] += 1;
		if (config->sim_state[1] == config->nb_philo)
		{
			pthread_mutex_lock(&config->sim_mutex[0]);
			config->sim_state[0] = 0;
			pthread_mutex_unlock(&config->sim_mutex[0]);
			config->life = 0;
		}
		pthread_mutex_unlock(&config->sim_mutex[1]);
	}
	return ;
}

void	solo(t_config *config)
{
	int	start;

	start = get_time('n');
	while (start + config->t_die > get_time('n'))
		;
	msg(config, DIES);
	config->life = 0;
}
