#include "../includes/philo_bonus.h"

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

static void	ft_kill_philosophers(t_arg *args)
{
	size_t	i;

	i = 0;
	while (i < args->all_philos->nbr_philo)
	{
		kill(args->all_philos[i].philo_id, SIGKILL);
		i++;
	}
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
		philos[i].philo_id = 0;
		philos[i].nbr_philo = args->nbr_philo;
		philos[i].total_nbr_of_meals = 0;
		philos[i].total_nbr_of_meals_1 = args->nbr_of_meals;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].time_of_last_meal = ft_time();
		philos[i].limit_of_life = args->time_to_die;
		philos[i].stop = 0;
		i++;
	}
	args->all_philos = philos;
}

void	taking_forks_eating(t_philo *philo)
{
	sem_wait(philo->fork_sem);
	sem_wait(philo->write_sem);
	printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
	sem_post(philo->write_sem);
	sem_wait(philo->fork_sem);
	sem_wait(philo->write_sem);
	printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id + 1);
	printf("%ld %d is eating\n", ft_time() - philo->start_time, philo->philo_id + 1);
	sem_post(philo->write_sem);
	philo->total_nbr_of_meals += 1;
	philo->time_of_last_meal = ft_time();
	ft_usleep(philo->time_to_eat);
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
}

void	sleeping_thinking(t_philo *philo)
{
	sem_wait(philo->write_sem);
	printf("%ld %d is sleeping\n", ft_time()- philo->start_time, philo->philo_id + 1);
	sem_post(philo->write_sem);
	ft_usleep(philo->time_to_sleep);
	sem_wait(philo->write_sem);
	printf("%ld %d is thinking\n", ft_time()- philo->start_time, philo->philo_id + 1);
	sem_post(philo->write_sem);
}

int ft_cnt_of_meals(t_philo *philo)
{
	int flag_enough;
	int i;
	if (philo->total_nbr_of_meals != -1 && philo->total_nbr_of_meals_1 > 0)
	{
		flag_enough = 1;
		i = -1;
		while(++i < philo->nbr_philo)
			if(philo[i].total_nbr_of_meals < philo->total_nbr_of_meals_1)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while(i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
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
	while(1)
	{
		i = -1;
		while(++i < philo->nbr_philo)
		{
			long time_now = ft_time();
			if (time_now -  philo[i].time_of_last_meal > philo[i].limit_of_life)
			{
				philo->arg->dead = 1;
				sem_wait(philo->write_sem);
				printf("%ld %d died\n", ft_time() - philo->start_time, philo[i].philo_id + 1);
				i = -1;
				while(i < philo[i].nbr_philo)
				{
					philo[i].stop = 1;
					i++;
				}
				sem_post(philo->write_sem);
				return (NULL);
			}
		}
		if (ft_cnt_of_meals(philo) || philo->stop)
			return(NULL);
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
		taking_forks_eating(philo);
		sleeping_thinking(philo);
	}
	return (NULL);
}

void ft_init_thread(t_arg *args)
{
	pthread_t		s_tid;

	pthread_create(&s_tid, NULL, ft_galina_monitor, (void *)args->all_philos);
	pthread_join(s_tid, NULL);
}

int	ft_launch_simulation(t_arg *args)
{
	int i;

	i = -1;
	while (++i < args->all_philos->nbr_philo)
	{
		args->all_philos[i].philo_id = fork();
		if (args->all_philos[i].philo_id  < 0)
			printf("Failed forking child..");
		// else if (args->all_philos[i].philo_id  == 0)
		// 	ft_init_thread(&args->all_philos[i]);
	}

	if (args->all_philos[0].philo_id> 0)
	{
		i = -1;
		while (++i < args->all_philos->nbr_philo)
			waitpid(args->all_philos[i].philo_id, &args->all_philos[i].child_status, 0);
	}
	return (0);
}

void	ft_semaphore_init(t_arg *args)
{
	sem_unlink("/semaphor_for_writing");
	sem_unlink("/semaphor_for_fork");
	args->all_philos->write_sem = sem_open("/semaphor_for_writing", O_CREAT, S_IRWXU, 1);//S_IRWXU for your own access
	args->all_philos->fork_sem = sem_open("/semaphor_for_fork",
			O_CREAT, S_IRWXU, args->all_philos->nbr_philo);
}

int ft_init_args(t_arg *args, int argc, char **argv)
{
	if (ft_is_digit(argv) != 0)
		return (1);
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	if (argc == 5)
	{
		if (args->nbr_philo < 1)
			return (0);
		args->nbr_of_meals = -1;
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
	ft_init_thread(&args);
	ft_semaphore_init(&args);
	ft_init_philosophers(&args);
	ft_launch_simulation(&args);
	ft_kill_philosophers(&args);
	return(0);
}
