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

#endif
