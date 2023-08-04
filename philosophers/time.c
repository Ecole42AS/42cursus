/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:57:16 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 18:57:19 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* if flag == 'i', initializes the timeofday,
	if flag == 'n', returns the time as of now
	else return the difference with the current time */
int	get_time(char c)
{
	struct timeval			tv;
	static struct timeval	start_time;

	if (c == 'i')
	{
		gettimeofday(&start_time, NULL);
		return (0);
	}
	else if (c == 'n')
	{
		gettimeofday(&tv, NULL);
		return ((tv.tv_sec - start_time.tv_sec) * 1000
			+ (tv.tv_usec - start_time.tv_usec) / 1000);
	}
	return (0);
}
