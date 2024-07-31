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

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
	usleep(1000);
}

void take_forks(t_philo *philo)
{
	t_table *table = philo->table;

	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_message("has taken a fork", philo);
}
void	eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	print_message("is eating", philo);
	philo->last_meal = get_time();
	usleep(table->time_to_eat * 1000);

	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	print_message("has put down forks", philo);

}
void philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(philo->table->time_to_sleep * 1000);
}
