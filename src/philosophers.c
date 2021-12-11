#include "../includes/philo.h"

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void free_all(t_arg *args)
{
	free(args->tids);
	free(args->all_philos);
	free(args->forks);
}

void 	unlock_and_destroy_mutex(t_arg *args)
{
	int nbr_ph = args->nbr_philo;
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while(nbr_ph--)
	{
		pthread_mutex_unlock(&mutex[nbr_ph]);
		pthread_mutex_destroy(&mutex[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock_print);
	pthread_mutex_destroy(&(*args).lock_print);
}

void	detach_all_threads(t_arg *args)
{
	int nbr_ph = args->nbr_philo;
	pthread_t		*threads;
	pthread_t		s_tid;

	threads = malloc(sizeof(pthread_t) * nbr_ph);
	while(nbr_ph--)
		pthread_detach(threads[nbr_ph]);
	pthread_detach(s_tid);
}

void	ft_check_args(void)
{
	printf(" ____________________________________________________ \n");
	printf("|            Please enter 4 or 5 arguments           |\n");
	printf("|____________________________________________________|\n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time to die]                       |\n");
	printf("|             [3][Time to eat]                       |\n");
	printf("|             [4][Time to sleep]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|____________________________________________________|\n");
}

void	ft_clear(t_arg *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philo)
	{
		pthread_mutex_destroy(args->all_philos[i].l_f);
		i++;
	}
	pthread_mutex_destroy(&args->lock_print);
	free(args->all_philos);
}

int	ft_exit(t_arg *args, int exit_code)
{
	if (exit_code == 1)
		return(1);
	ft_check_args();
	return(0);
}

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * i);
}

int	ft_is_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void ft_init_philosophers(t_arg *args)
{
	int i;
	i = 0;
	t_philo *philos = malloc(sizeof(t_philo) * args->nbr_philo);

	while(i < args->nbr_philo)
	{
		philos[i].philo_id = i;
		philos[i].nbr_philo = args->nbr_philo;
		philos[i].total_nbr_of_meals = 0;
		philos[i].total_nbr_of_meals_1 = args->nbr_of_meals;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].time_of_last_meal = ft_time();
		philos[i].limit_of_life = args->time_to_die;
		philos[i].stop = 0;
		philos[i].l_f = &args->forks[philos[i].philo_id];
		philos[i].r_f = &args->forks[(philos[i].philo_id + 1) % args->nbr_philo];
		i++;
	}
	args->all_philos = philos;
}

void	taking_forks(t_philo *philo)
{
	if((philo->philo_id) % 2 == 0 && philo->philo_id + 1 != philo->nbr_philo)
	{
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(&philo->lock_print);
		printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->lock_print);
	}
	else
	{
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(&philo->lock_print);
		printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->lock_print);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->total_nbr_of_meals += 1;
	if (philo->total_nbr_of_meals == philo->total_nbr_of_meals_1)
	{
		philo->stop = 1;
		pthread_mutex_unlock(philo->l_f);
		pthread_mutex_unlock(philo->r_f);
	}
	philo->time_of_last_meal = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", ft_time()- philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", ft_time()- philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}

int ft_cnt_of_meals(t_philo *philo)
{
	int flag_enough;
	int i;
	if (philo->total_nbr_of_meals != -1)
	{
		flag_enough = 1;
		i = -1;
		while(++i < philo->nbr_philo)
		{
			if(philo[i].total_nbr_of_meals < philo->total_nbr_of_meals_1)
				flag_enough = 0;
		}

		if (flag_enough == 1)
		{
			pthread_mutex_lock(&philo->lock_print);
			printf ("All philosophers have eaten at least  ");
			printf (" %d times each\n", philo->total_nbr_of_meals);
			pthread_mutex_unlock(&philo->lock_print);
			i = -1;
			while(++i < philo->nbr_philo)
			{
				printf ("philosopher %d", philo[i].philo_id + 1);
				printf (" total eat = %d\n", philo[i].total_nbr_of_meals);
			}
			return(1);
		}
	}
	return(0);
}

void *ft_galina_monitor(void *args)
{
	t_philo *philo;
	int i;
	philo = (t_philo *)args;
	//philo->time_of_last_meal = philo->start_time = ft_time();
	while(1)
	{
		i = -1;
		while(++i < philo->nbr_philo)
		{
			long time_now = ft_time();
			if (time_now -  philo[i].time_of_last_meal > philo[i].limit_of_life)
			{
				printf("%ld LAST\n", philo[i].time_of_last_meal);
				printf("%ld LIMIT\n", philo[i].limit_of_life);
				printf("%ld NOW\n", time_now);
				printf("%ld DIF\n", time_now - philo[i].time_of_last_meal);
				pthread_mutex_lock(&philo->lock_print);
				printf("%ld %d DIED\n", ft_time() - philo->start_time, philo->philo_id + 1);
				//exit(0);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (ft_cnt_of_meals(philo))
			exit(0);
	}
	return(NULL);
}

void *ft_process(void *args)
{
	t_philo		*philo;
	philo = (t_philo *)args;
	philo->time_of_last_meal = philo->start_time = ft_time();
	while (1)
	{
		if (ft_cnt_of_meals(philo))
			return(NULL);
		taking_forks(philo);
		if (ft_cnt_of_meals(philo))
			return(NULL);
		eating(philo);
		if (ft_cnt_of_meals(philo))
			return(NULL);
		sleeping(philo);
		if (ft_cnt_of_meals(philo))
			return(NULL);
		thinking(philo);
		if (ft_cnt_of_meals(philo))
			return(NULL);
	}
	return (NULL);
}

void ft_init_mutex(t_arg *args)
{
	int nbr_ph = args->nbr_philo;
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while(nbr_ph--)
		pthread_mutex_init(&mutex[nbr_ph], NULL);
	pthread_mutex_init(&args->lock_print, NULL);
	args->forks = mutex;
}

void ft_init_threads(t_arg *args)
{
	int nbr_ph = args->nbr_philo;
	pthread_t		*threads;
	pthread_t		s_tid;
	t_philo philo;
	int i = -1;

	threads = malloc(sizeof(pthread_t) * nbr_ph);
	while(nbr_ph--)
		pthread_create(&threads[nbr_ph], NULL, ft_process, (void *)&args->all_philos[nbr_ph]);
	pthread_create(&s_tid, NULL, ft_galina_monitor, (void *)args->all_philos);
	pthread_join(s_tid, NULL);
	// while (++i < args->nbr_philo)
	// 	pthread_mutex_destroy(&args[0].forks[i]);
	args->tids = threads;
}

void ft_end_threads(t_arg *args)
{
	int nbr_ph = args->nbr_philo;

	nbr_ph = args->nbr_philo;
	while(nbr_ph)
	{
		nbr_ph--;
		pthread_join(args->tids[nbr_ph], NULL);
	}
}

int ft_init_args(t_arg *args, int argc, char **argv)
{
	if (ft_is_digit(argv) != 0)
		return (1);
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	if (argc == 5)
	{
		if (args->nbr_philo < 1)
			return (0);
		args->nbr_of_meals= -1;
	}
	if (argc == 6)
	{
		if (args->nbr_of_meals < 1)
			return (0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_arg	args;

	if (argc < 5 || argc > 6)
	{
		ft_check_args();
		return (0);
	}
	if (ft_init_args(&args, argc, argv) == 1)
	{
		return 1;
	}
	ft_init_mutex(&args);
	ft_init_philosophers(&args);
	ft_init_threads(&args);
	ft_end_threads(&args);
	detach_all_threads(&args);
	unlock_and_destroy_mutex(&args);
	free_all(&args);
	return(0);
}
