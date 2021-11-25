#include "../includes/philo.h"

int	ft_time(void)
{
	struct timeval	tv;
	time_t			res;

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

// void display_message(t_philo *philo, int message)
// {

// }

void ft_init_philosophers(t_arg *args)
{
	int i;
	i = 0;
	//t_philo philos[args->nbr_philo];//куча структур, philos указатель на первого фило(по кол-ву философов)
	t_philo *philos = malloc(sizeof(t_philo) * args->nbr_philo);
	//philo->stop = 0;
	while(i < args->nbr_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].nbr_of_meals = 0;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].time_of_last_meal = 0;
		philos[i].limit_of_life = args->time_to_die;
		philos[i].dead = 0;
		philos[i].stop = 0;
		philos[i].l_f = &args->forks[philos[i].philo_id];
		philos[i].r_f = &args->forks[(philos[i].philo_id + 1) % args->nbr_philo];
		i++;
	}
	args->all_philos = philos;
}

void debug(t_arg *args)
{
	int i;
	i = 0;
	t_philo *philos = malloc(sizeof(t_philo) * args->nbr_philo);
	args->all_philos = philos;
	//printf("\nPhilosophers = %i\n", philos[i].philo_id);
	printf("Time to die = %ims\n", philos[i].time_to_die);
	printf("Time to eat = %ims\n", philos[i].time_to_eat);
	printf("Time to sleep = %ims\n", philos[i].time_to_sleep);
	//printf("Must eat = %li times each\n", philos[i].args->eat_times);
	printf("\n------------------------------------------\n");
	while(i < args->nbr_philo)
	{
		printf("Philo number #%d\n", philos[i].philo_id);
		//printf("Is alive %d\n", philos[i].is_alive);
		printf("Fork on left hand %d\n", *(int *)philos[i].l_f);
		printf("Fork on right hand %d\n", *(int *)philos[i].r_f);
		//printf("Must eat times %d\n", philos[i].must_eat_times);
		printf("Last meal %li\n", philos[i].time_of_last_meal);
		printf("\n------------------------------------------\n");
		i++;
	}
}

void	taking_forks(t_philo *philo)
{
	if((philo->philo_id + 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->r_f);
		// pthread_mutex_lock(&philo->lock_print);
		// printf("%ld %d has taken a right fork\n", ft_time()- philo->start_time, philo->philo_id);
		// pthread_mutex_unlock(&philo->lock_print);
		// pthread_mutex_lock(&philo->lock_print);
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(&philo->lock_print);
		printf("%ld %d has taken a right fork\n", ft_time()- philo->start_time, philo->philo_id);
		printf("%ld %d has taken a left fork\n", ft_time()- philo->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->lock_print);
	}
	else
	{
		pthread_mutex_lock(philo->l_f);
		// pthread_mutex_lock(&philo->lock_print);
		// printf("%ld %d has taken a right fork\n", ft_time()- philo->start_time, philo->philo_id);
		// pthread_mutex_unlock(&philo->lock_print);
		// pthread_mutex_lock(&philo->lock_print);
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(&philo->lock_print);
		printf("%ld %d has taken a left fork\n", ft_time()- philo->start_time, philo->philo_id);
		printf("%ld %d has taken a right fork\n", ft_time()- philo->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->lock_print);
	}
	//pthread_mutex_lock(&args->lock_print);
	//printf("%ld %d has taken a fork\n", ft_time()- philo->start_time, philo->philo_id);
	//display_message();//has taken a fork
	//pthread_mutex_unlock(&args->lock_print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", ft_time() - philo->start_time, philo->philo_id);
	//display_message();//is eating
	pthread_mutex_unlock(&philo->lock_print);
	philo->nbr_of_meals +=1;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", ft_time()- philo->start_time, philo->philo_id);
	//display_message();//sleeping
	pthread_mutex_unlock(&philo->lock_print);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", ft_time()- philo->start_time, philo->philo_id);
	//display_message();//thinking
	pthread_mutex_unlock(&philo->lock_print);
}

void *ft_process(t_philo *raw_philo)
{
	t_philo		philo = *raw_philo;
	philo.start_time = ft_time();
	while (1)
	{
		if(ft_time() - philo.time_of_last_meal > philo.limit_of_life)
		{
			//philo.time_of_last_meal = ft_time();
			taking_forks(&philo);
			eating(&philo);
			sleeping(&philo);
			thinking(&philo);
		}
		else
		{
			printf("%ld %d is dead\n", ft_time()- philo.start_time, philo.philo_id);
			return(NULL);
		}
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
	//pthread_mutex_init(&args->set_id, NULL);
	//pthread_mutex_init(&args->lock_print, NULL);
	args->forks = mutex;
}

void ft_init_threads(t_arg *args)
{
	int nbr_ph = args->nbr_philo;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while(nbr_ph--)
		pthread_create(&threads[nbr_ph], NULL, (void *)ft_process, &args->all_philos[nbr_ph]);
	args->tids = threads;
}

void ft_end_threads(t_arg *args)
{
	int nbr_ph = args->nbr_philo;

	nbr_ph = args->nbr_philo;
	while(nbr_ph--)
		pthread_join(args->tids[nbr_ph], NULL);
}

void ft_init_args(t_arg *args, int argc, char **argv)
{
	args->nbr_philo = ft_atoi(argv[1]);
	if (args->nbr_philo == 0)
		return ;
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	//args->start_time = ft_time();
	return ;
}

int	ft_check_args(int argc)
{
	if (argc < 5 || argc > 6)
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
		return (0);
	}
	return(1);

}

int main(int argc, char **argv)
{
	t_arg	args;

	ft_check_args(argc);
	ft_init_args(&args, argc, argv);
	ft_init_mutex(&args);
	ft_init_philosophers(&args); //вернется указатель на всех замоллоченных фило
	ft_init_threads(&args);
	ft_end_threads(&args);

	return(0);
}
