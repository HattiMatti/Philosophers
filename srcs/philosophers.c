/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:00:37 by msiitone          #+#    #+#             */
/*   Updated: 2024/06/12 19:00:51 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->nbr_of_philos);
	if (table->philos == NULL)
	{
		free_all(table);
		return ;
	}
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nbr_of_philos);
	if (table->forks == NULL)
	{
		free_all(table);
		return ;
	}
	while (i < table->nbr_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			erfre(table, i);
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
		erfre(table, i);
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		table->philos[i].id = i;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->nbr_of_philos;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		i++;
	}
}	
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;

	while (1)
	{
		print_message("is thinking", philo);
		usleep(1000000);

		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_message("has taken a fork", philo);

		print_message("is eating", philo);
		usleep(2000000);

		pthread_mutex_unlock(&table->forks[philo->right_fork]);
        pthread_mutex_unlock(&table->forks[philo->left_fork]);
        print_message("has put down a fork", philo);
        print_message("has put down a fork", philo);

		print_message("is sleeping", philo);
        usleep(1500000);
	}
	return NULL;
}
