/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:54 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 21:52:55 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_taking_forks_eating(t_arg *args)
{
	sem_wait(args->fork_sem);
	sem_wait(args->fork_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu is eating\n", ft_time() - args->start_time, \
		args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	args->philo.time_of_last_meal = ft_time();
	args->philo.total_nbr_of_meals += 1;
	if (args->philo.total_nbr_of_meals == args->nbr_of_meals)
		sem_post(args->eat_enough);
	ft_usleep(args->time_to_eat);
	sem_post(args->fork_sem);
	sem_post(args->fork_sem);
}

void	ft_sleeping_thinking(t_arg *args)
{
	sem_wait(args->write_sem);
	printf("%ld %lu is sleeping\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	ft_usleep(args->time_to_sleep);
	sem_wait(args->write_sem);
	printf("%ld %lu is thinking\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
}

void	*ft_routine(void *args)
{
	t_arg	*philo;

	philo = (t_arg *)args;
	philo->start_time = ft_time();
	while (1)
	{
		ft_taking_forks_eating(philo);
		ft_sleeping_thinking(philo);
	}
	return (NULL);
}

void	*ft_eating_checker(void *arg)
{
	t_arg	*args;
	int		i;

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

void	*ft_death_checker(void *arg)
{
	t_arg	*args;
	long	time_now;

	args = arg;
	while (1)
	{
		time_now = ft_time();
		if (time_now - args->philo.time_of_last_meal > args->time_to_die)
		{
			sem_wait(args->write_sem);
			printf("%ld %lu died\n", \
				ft_time() - args->start_time, args->philo.philo_ind + 1);
			sem_post(args->stop);
			exit(0);
		}
	}
	return (NULL);
}
