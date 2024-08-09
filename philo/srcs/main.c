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
	table->nbr_of_philos = (ft_atoi(argv[1]));
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nbr_of_meals = ft_atoi(argv[5]);
	else
		table->nbr_of_meals = -1;
}

void	create_threads(t_table *table)
{
	int	i;

	table->start = get_time();
	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_create(&table->philos[i].thread, NULL,
			philosopher_routine, &table->philos[i]);
		i++;
	}
	pthread_create(&table->monitor_thread, NULL, monitor, table);
	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (argc == 5 || argc == 6)
	{
		if (is_pos(argc, argv) == 1 || check_args(argc, argv) == 1)
		{
			ft_putstr_fd("Error: Invalid arguments\n", 2);
			return (EXIT_FAILURE);
		}
		parse_args(argc, argv, &table);
		init_table(&table);
		pthread_mutex_init(&table.death, NULL);
		init_philos(&table);
		create_threads(&table);
		free_end(&table);
	}
	else
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
	return (EXIT_SUCCESS);
}
