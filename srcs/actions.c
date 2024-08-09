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
	pthread_mutex_lock(&table->forks[philo->first_fork]);
	philo->forks_locked = 1;
	if (print_message("has taken a fork", philo) != 0)
	{
		pthread_mutex_unlock(&table->forks[philo->first_fork]);
		return (-1);
	}
	pthread_mutex_lock(&table->forks[philo->second_fork]);
	if (print_message("has taken a fork", philo) != 0)
	{
		release_forks(philo);
		return (-1);
	}
	philo->forks_locked = 2;
	return (0);
}

int	eat(t_philo *philo)
{
	if (has_philosopher_died(philo))
		return (-1);
	pthread_mutex_lock(&philo->eat_mutex);
	if (print_message("is eating", philo) != 0)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (-1);
	}
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	pthread_mutex_lock(&philo->table->death);
	philo->last_meal = get_time();
	if (philo->table->nbr_of_meals != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->death);
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	usleep(philo->table->time_to_eat * 1000);
	release_forks(philo);
	if (print_message("has put down forks", philo) != 0)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
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
	if (philo->forks_locked == 2)
	{
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
	}
	else if (philo->forks_locked == 1)
		pthread_mutex_unlock(&table->forks[philo->first_fork]);
	philo->forks_locked = 0;
}
