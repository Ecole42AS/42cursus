/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:57:01 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 18:57:05 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* frees and terminates the program philo */
void	terminate(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(philo->sim_mutex);
	while (++i <= philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
	}
	free(philo->threads);
	free(philo->forks);
	free(philo->sim_mutex);
	free(philo->sim_state);
	free(philo);
}
