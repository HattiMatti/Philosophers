/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:36:15 by msiitone          #+#    #+#             */
/*   Updated: 2024/07/22 17:36:17 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	think(t_philo *philo)
{
	if (has_philosopher_died(philo))
		return (-1);
	if (print_message("is thinking", philo) != 0)
		return (-1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (determine_forks(philo) != 0 || has_philosopher_died(philo))
		return (-1);
	if (pthread_mutex_lock(&table->forks[philo->first_fork]) != 0)
		return (-1);
	if (print_message("has taken a fork", philo) != 0)
	{
		pthread_mutex_unlock(&table->forks[philo->first_fork]);
		return (-1);
	}
	if (pthread_mutex_lock(&table->forks[philo->second_fork]) != 0)
	{
		pthread_mutex_unlock(&table->forks[philo->first_fork]);
		return (-1);
	}
	if (print_message("has taken a fork", philo) != 0)
	{
		pthread_mutex_unlock(&table->forks[philo->first_fork]);
		pthread_mutex_unlock(&table->forks[philo->second_fork]);
		return (-1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (has_philosopher_died(philo))
		return (-1);
	if (print_message("is eating", philo) != 0)
		return (-1);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (table->nbr_of_meals != -1)
		philo->meals_eaten++;
	usleep(table->time_to_eat * 1000);
	if (pthread_mutex_unlock(&table->forks[philo->left_fork]) != 0)
		return (-1);
	if (pthread_mutex_unlock(&table->forks[philo->right_fork]) != 0)
		return (-1);
	if (print_message("has put down forks", philo) != 0)
		return (-1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (has_philosopher_died(philo))
		return (-1);
	if (print_message("is sleeping", philo) != 0)
		return (-1);
	usleep(philo->table->time_to_sleep * 1000);
	return (0);
}

void	release_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (pthread_mutex_unlock(&table->forks[philo->left_fork]) != 0)
	{
		fprintf(stderr, "Error: Failed to unlock left fork mutex\n");
	}
	if (pthread_mutex_unlock(&table->forks[philo->right_fork]) != 0)
	{
		fprintf(stderr, "Error: Failed to unlock right fork mutex\n");
	}
}
