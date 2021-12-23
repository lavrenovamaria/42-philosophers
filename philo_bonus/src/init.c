/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:58 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 22:12:51 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

void	ft_init_philo(t_arg *args)
{
	args->philo.time_of_last_meal = ft_time();
	if (pthread_create(&args->galina_tid, NULL, &ft_death_checker, args))
	{
		printf("Error pthread");
		sem_post(args->stop);
	}
	pthread_detach(args->galina_tid);
}

static int	ft_init_sempahore(t_arg *args)
{
	sem_unlink("fork_sem");
	sem_unlink("write_sem");
	sem_unlink("stop");
	sem_unlink("eat_enough");
	args->fork_sem = sem_open("fork_sem", O_CREAT | \
		O_EXCL, S_IRWXU, args->nbr_philo);
	args->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	args->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (args->nbr_of_meals)
		args->eat_enough = sem_open("eat_enough", O_CREAT | O_EXCL, S_IRWXU, 0);
	return (0);
}

int	ft_init_args(t_arg *args, int argc, char **argv)
{
	memset(args, 0, sizeof(t_arg));
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
