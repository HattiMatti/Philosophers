/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:58:31 by msiitone          #+#    #+#             */
/*   Updated: 2024/06/11 16:06:34 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(args));
	if (argc == 5 || argc == 6)
	{
		args.nbr_of_philo = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.nbr_of_meals = ft_atoi(argv[5]);
	}
	else
	{
		ft_putstr_fd("Error: wrong number of arguments", 2);
	}
	printf("%d, %d, %d, %d, %d", args.nbr_of_philo, args.time_to_die,
		args.time_to_eat, args.time_to_sleep, args.nbr_of_meals);
	return (0);
}
