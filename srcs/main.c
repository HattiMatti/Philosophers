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

void	parse_args(int argc, char **argv, t_table *table)
{
	table->nbr_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nbr_of_meals = ft_atoi(argv[5]);
	else
		table->nbr_of_meals = -1;
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (argc == 5 || argc == 6)
	{
		parse_args(argc, argv, &table);
		printf("%d, %d, %d, %d, %d\n", table.nbr_of_philos, table.time_to_die,
			table.time_to_eat, table.time_to_sleep, table.nbr_of_meals);
		print_message("TESTING", &table);	
	}
	else
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
	return (0);
	
}
