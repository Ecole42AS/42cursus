/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:13:00 by astutz            #+#    #+#             */
/*   Updated: 2023/08/07 19:33:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** =============================================================================
** Dependencies
** =============================================================================
*/

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

/*
** =============================================================================
** Enum Type Definitions
** =============================================================================
*/

/*
** =============================================================================
** Struct Type Definitions
** =============================================================================
*/

typedef struct s_philos_stats
{
	int	philos_numbers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_goal;

}	t_philos_stats;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			is_taken;
}					t_fork;
/*Contrôle la fin de la simulation
finish_counter; //nb de philos qui ont finis leurs repas
status; //savoir si la simulation doit continuer ou se terminer.*/
typedef struct s_stop
{
	pthread_mutex_t	*mutex;
	int				finish_counter;
	bool			status;
}					t_stop;

typedef struct s_philo
{
	int					id;
	int					philos_numbers;
	t_fork				*forks;
	int					last_eat_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	bool				is_dead;
	int					fork_in_hand_numbers;
	int					meal_number;
	int					meal_goal;
	t_stop				*stop;

}						t_philo;

/*informations d'initialisation partagées 
pour tous les philosophes*/
typedef struct s_init_data
{
	int				i;
	t_philos_stats	philos_stats;
	t_fork			*forks;
	t_stop			*stop;
}				t_init_data;

/*
** =============================================================================
** Functions
** =============================================================================
*/
//	philo.c
void	*brain(void *args);
void	die(t_philo *philo);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	dream(t_philo *philo);
// fork.c
bool	take_fork(t_philo *philo, t_fork *fork);
void	release_fork(t_fork *fork);
//	utils.c
void	logs(char *msg, t_philo *philo, bool kill);
int		get_time_ms(void);
int		ft_atoi(char *str);
void	free_all(t_philo *philos);
#endif