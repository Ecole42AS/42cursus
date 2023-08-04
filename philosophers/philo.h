/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:05:10 by astutz            #+#    #+#             */
/*   Updated: 2023/08/04 18:45:16 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define EATS 1
# define SLEEPS 2
# define THINKS 3
# define DIES 4
# define FORKS 5

typedef struct s_philo
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*sim_mutex;
	int				*sim_state;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_eat;
}				t_philo;

typedef struct s_config
{
	int				pos;
	int				next_pos;
	int				nb_philo;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				nb_t_eat;
	int				life;
	int				ate;
	int				last_bite;
	int				*sim_state;
	pthread_mutex_t	*sim_mutex;
	pthread_mutex_t	*forks;
}				t_config;

// errors

int			infos_check(char **infos, int nb_args);
int			error_msg(char flag);

// time

int			get_time(char c);

// msg

void		msg(t_config *config, int status);

// actions

void		eats(t_config *config);
void		sleeps(t_config *config);
void		thinks(t_config *config);

// sim

void		launch_sim(t_philo **philo);
int			satiated(t_config *config);

// state

int			state(t_config *config);
void		state_update(t_config *config, char flag);

// terminate

void		terminate(t_philo *philo);

#endif