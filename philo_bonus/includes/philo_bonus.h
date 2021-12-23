/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:48 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 21:52:49 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include "philo_bonus.h"

typedef struct s_philo
{
	pthread_t	galina_tid;
	sem_t		*actions;
	size_t		philo_ind;
	size_t		total_nbr_of_meals;
	time_t		time_of_last_meal;
	int			nbr_of_meals;
}				t_philo;

typedef struct s_arg
{
	pthread_t	galina_tid;
	pid_t		*pid_philo;
	sem_t		*write_sem;
	sem_t		*fork_sem;
	sem_t		*stop;
	sem_t		*eat_enough;
	int			nbr_philo;
	time_t		start_time;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	size_t		nbr_of_meals;

	t_philo		philo;

}				t_arg;

void	ft_taking_forks_eating(t_arg *args);
void	ft_sleeping_thinking(t_arg *args);
void	*ft_routine(void *args);
void	*ft_eating_checker(void *arg);
void	*ft_death_checker(void *arg);
int		ft_init_args(t_arg *args, int argc, char **argv);
void	ft_init_philo(t_arg *args);
long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);

#endif
