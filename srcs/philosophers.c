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
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->nbr_of_philos);
	if (table->forks == NULL)
	{
		free_all(table);
		return ;
	}
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->last_meal_mutex, NULL);
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
		table->philos[i].first_fork = 0;
		table->philos[i].second_fork = 0;
		table->philos[i].forks_locked = 0;
		pthread_mutex_init(&table->philos[i].eat_mutex, NULL);
		i++;
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (has_philosopher_died(philo))
			break ;
		if (take_forks(philo) != 0 || has_philosopher_died(philo))
		{
			release_forks(philo);
			break ;
		}
		if (eat(philo) != 0 || has_philosopher_died(philo))
		{
			break ;
		}
		if (philo_sleep(philo) != 0 || has_philosopher_died(philo))
		{
			break ;
		}
		think(philo);
	}
	return (NULL);
}

int	determine_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->nbr_of_philos == 1)
	{
		print_message("has taken a fork", philo);
		usleep(table->time_to_die * 1000);
		return (1);
	}
	fork_wait(philo);
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
	return (0);
}

void	fork_wait(t_philo *philo)
{
	t_table	*table;
	int		wait_time;

	table = philo->table;
	wait_time = (table->time_to_eat / 10) * 1000;
	if (philo->id % 2 == 0)
	{
		usleep(wait_time);
	}
	else
	{
		usleep(wait_time / 2);
	}
}
