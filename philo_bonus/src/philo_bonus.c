/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:52:41 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 21:52:42 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

static int	ft_check_valid(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		ft_check_args();
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
		{
			printf("Invalid argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	args;

	if (ft_check_valid(argc, argv))
		return (1);
	if (ft_init_args(&args, argc, argv) == 1)
		return (1);
	if (ft_start_philo(&args))
		return (1);
	ft_kill_philosophers(&args);
	return (0);
}
