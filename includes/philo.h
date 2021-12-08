#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo.h"

struct s_arg;

typedef struct		s_philo
{
	int				philo_id;//id of philosopher
	int				total_nbr_of_meals;//!!!!!!!!!!!!!!!!!
	int				total_nbr_of_meals_1;
	time_t			time_of_last_meal;//time when philo last eat im ms
	int				nbr_philo; //arg1
	int				time_to_eat; //arg3
	int				time_to_die; //arg2
	int				time_to_sleep; //arg4
	time_t			limit_of_life;//when time_of_last_meal > limit_of_life --> dead
	int				stop;//true if philosopher ate time_of_last_meal arg5
	time_t			start_time;
	pthread_mutex_t	lock_print; //for printf
	pthread_mutex_t	*l_f;//left fork = id of philo
	pthread_mutex_t	*r_f;
	struct s_arg			*arg;
}					t_philo;

typedef struct		s_arg
{
	int				nbr_philo; //arg1
	int				philo_id;
	time_t			start_time;
	int				time_to_die; //arg2
	int				time_to_eat; //arg3
	int				time_to_sleep; //arg4
	int				nbr_of_meals; //!!!!!!!!
	pthread_mutex_t	*forks;
	pthread_t		*tids;//id of the threads //start time in milliseconds
	pthread_mutex_t	lock_print; //for printf
	t_philo			*all_philos;
}					t_arg;

#endif
