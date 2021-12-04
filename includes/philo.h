#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define THINKING "%6lu %3d   is thinking\n"
# define TAKEN_FORK "%6lu %3d   has taken a fork\n"
# define SLEEPING "%6lu %3d   is sleeping\n"
# define EATING "%6lu %3d   is eating\n"
# define DIED "%6lu %3d   died\n"

typedef enum e_bool {
	false,
	true
}				t_bool;

typedef struct		s_philo
{
	int				philo_id;//id of philosopher
	int				nbr_of_meals;//each time the philosopher eats -> nbr++
	time_t			time_of_last_meal;//time when philo last eat im ms
	int				nbr_philo; //arg1
	int				time_to_eat; //arg3
	int				time_to_die; //arg2
	int				time_to_sleep; //arg4
	time_t			limit_of_life;//when time_of_last_meal > limit_of_life --> dead
	t_bool			stop;//true if philosopher ate time_of_last_meal arg5
	//t_bool			dead;//
	time_t			start_time;
	pthread_mutex_t	lock_print; //for printf
	pthread_mutex_t	*l_f;//left fork = id of philo
	pthread_mutex_t	*r_f;//pointer ti right fork
}					t_philo;

typedef struct		s_arg
{
	int				nbr_philo; //arg1
	int				philo_id;
	time_t			start_time;
	int				time_to_die; //arg2
	int				time_to_eat; //arg3
	int				time_to_sleep; //arg4
	int				nbr_of_meals; //arg5
	int				cnt_of_meals; //when a philosopher ate nbr_of_meals times -> counter++
	pthread_mutex_t	*forks;
	pthread_t		*tids;//id of the threads //start time in milliseconds
	pthread_mutex_t	lock_print; //for printf
	t_philo			*all_philos;
}					t_arg;


#endif
