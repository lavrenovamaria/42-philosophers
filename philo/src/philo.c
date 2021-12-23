/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:31 by wrickard          #+#    #+#             */
/*   Updated: 2021/12/23 23:11:56 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	ft_init_mutex(&args);
	ft_init_philosophers(&args);
	ft_init_threads(&args);
	ft_end_threads(&args);
	unlock_and_destroy_mutex(&args);
	free_all(&args);
	return (0);
}
