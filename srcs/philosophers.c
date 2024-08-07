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
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->nbr_of_philos;
		table->philos[i].last_meal = get_time();
		table->philos[i].table = table;
		i++;
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->died == 0)
	{
		pthread_mutex_lock(&philo->table->death);
		if (philo->table->died)
		{
			pthread_mutex_unlock(&philo->table->death);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death);
		think(philo);
		take_forks(philo);
		printf("test");
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			i;
	long long	current_time;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->nbr_of_philos)
		{
			current_time = get_time();
			if (monitor_death(current_time, table, i) == 1)
				break ;
			monitor_meals(table, i);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
