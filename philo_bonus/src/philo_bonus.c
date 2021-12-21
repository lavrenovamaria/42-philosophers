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

void	ft_taking_forks_eating(t_arg *args)
{
	sem_wait(args->fork_sem);
	sem_wait(args->fork_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu has taken a fork\n", ft_time()- args->start_time, args->philo.philo_ind + 1);
	printf("%ld %lu has taken a fork\n", ft_time()- args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu is eating\n", ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	args->philo.time_of_last_meal = ft_time();
	args->philo.total_nbr_of_meals += 1;
	ft_usleep(args->time_to_eat);
	sem_post(args->fork_sem);
	sem_post(args->fork_sem);
}

void	ft_sleeping_thinking(t_arg *args)
{
	sem_wait(args->write_sem);
	printf("%ld %lu is sleeping\n", ft_time()- args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	ft_usleep(args->time_to_sleep);
	sem_wait(args->write_sem);
	printf("%ld %lu is thinking\n", ft_time()- args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
}

void	*ft_routine(void *args)
{
	t_arg	*philo;
	philo = (t_arg *)args;
	philo->start_time = ft_time();
	while (1)
	{
		//sem_wait(args->philo.actions);
		ft_taking_forks_eating(philo);
		ft_sleeping_thinking(philo);
	}
	//sem_post(args->philo.actions);
	return (NULL);
}

void	*ft_eating_checker(void *arg)
{
	t_arg *args;
	int	i;
	args = arg;
	i = -1;
	sem_wait(args->write_sem);
	while (++i < args->nbr_philo)
	{
		sem_post(args->write_sem);
		sem_wait(args->eat_enough);
		sem_wait(args->write_sem);
	}
	sem_post(args->stop);
	return (NULL);
}

// int ft_cnt_of_meals(void *arg)
// {
// 	t_arg *args;
// 	args = arg;
// 	int flag_enough;
// 	int i = 0;;
// 	if (args->philo.total_nbr_of_meals != -1 && args->nbr_of_meals > 0)
// 	{
// 		flag_enough = 1;
// 		i = -1;
// 		while(++i < args->nbr_philo)
// 			if(args->philo[i].total_nbr_of_meals < args->nbr_of_meals)
// 				flag_enough = 0;
// 		if (flag_enough == 1)
// 		{
// 			i = -1;
// 			while(i < args->philo[i].nbr_philo)
// 			{
// 				args->philo[i].stop = 1;
// 				i++;
// 			}
// 			return(1);
// 		}
// 	}
// 	return(0);
// }

void	*ft_death_checker(void *arg)
{
	t_arg *args;

	args = arg;
	while (1)
	{
		long time_now = ft_time();
		//sem_wait(args->philo.actions);
		if (time_now - args->philo.time_of_last_meal > args->time_to_die)
		{
			sem_wait(args->write_sem);
			printf("%ld %lu died\n", ft_time() - args->start_time, args->philo.philo_ind + 1);
			sem_post(args->stop);
		}
		//sem_post(args->philo.actions);
	}
	return (NULL);
}

void	ft_init_philo(t_arg *args)
{
	//args->philo.time_of_last_meal = args->start_time;
	args->philo.time_of_last_meal = ft_time();
	if (pthread_create(&args->galina_tid, NULL, &ft_death_checker, args))
	{
		printf("Error pthread");
		sem_post(args->stop);
	}
	pthread_create(&args->galina_tid, NULL, &ft_death_checker, args);
	pthread_detach(args->galina_tid);
}

static int	ft_init_sempahore(t_arg *args)
{
	sem_unlink("fork_sem");
	sem_unlink("write_sem");
	sem_unlink("stop");
	sem_unlink("eat_enough");
	args->fork_sem = sem_open("fork_sem", O_CREAT | O_EXCL, S_IRWXU, args->nbr_philo);
	args->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	args->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (args->nbr_of_meals)
		args->eat_enough= sem_open("eat_enough", O_CREAT | O_EXCL, S_IRWXU, 0);
	return (0);
}

static int	ft_init_galina(t_arg *args)
{
	if (args->nbr_of_meals)
	{
		if (pthread_create(&args->galina_tid, NULL, &ft_eating_checker, args))
		{
			printf("Error pthread");
			return (1);
		}
		pthread_detach(args->galina_tid);
	}
	return (0);
}

int	ft_start_philo(t_arg *args)
{
	int	i;

	i = 0;
	args->start_time = ft_time();
	while (i < args->nbr_philo)
	{
		args->philo.philo_ind = i;
		args->pid_philo[i] = fork();
		if (args->pid_philo[i] == -1)
		{
			while (--i >= 0)
				kill(args->pid_philo[i], SIGKILL);
			return (1);
		}
		else if (args->pid_philo[i] == 0)
		{
			ft_init_philo(args);
			ft_routine(args);
		}
		i++;
	}
	sem_wait(args->stop);
	return (0);
}

int ft_init_args(t_arg *args, int argc, char **argv)
{
	memset(args, 0, sizeof(t_arg));
	if (ft_is_digit(argv) != 0)
		return (1);
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	args->pid_philo = malloc(sizeof(pid_t) * args->nbr_philo);
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
	memset(args->pid_philo, 0, sizeof(pid_t) * args->nbr_philo);
	ft_init_sempahore(args);
	ft_init_galina(args);
	return (0);
}

static void	ft_kill_philosophers(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		kill(args->pid_philo[i], SIGKILL);
		i++;
	}
}

static void	ft_free_args(t_arg *args)
{
	free(args->pid_philo);
	sem_close(args->fork_sem);
	sem_close(args->write_sem);
	sem_close(args->stop);
	sem_close(args->eat_enough);
}

int	main(int argc, char **argv)
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
	ft_start_philo(&args);
	ft_kill_philosophers(&args);
	ft_free_args(&args);
	return(0);
}
