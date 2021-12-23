/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:39 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 23:07:40 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_arg *args)
{
	free(args->tids);
	free(args->all_philos);
	free(args->forks);
}

void	unlock_and_destroy_mutex(t_arg *args)
{
	int	nbr_ph;

	nbr_ph = args->nbr_philo;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&args->forks[nbr_ph]);
		pthread_mutex_destroy(&args->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock_print);
	pthread_mutex_destroy(&(*args).lock_print);
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
