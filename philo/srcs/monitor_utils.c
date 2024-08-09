/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:05:16 by msiitone          #+#    #+#             */
/*   Updated: 2024/08/09 19:05:20 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	monitor_death(int current_time, t_table *table, int i)
{
	pthread_mutex_lock(&table->death);
	if ((current_time - table->philos[i].last_meal) > table->time_to_die)
	{
		print_message("died", &table->philos[i]);
		table->died = 1;
		table->philos[i].died = 1;
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

void	monitor_meals(t_table *table)
{
	int	all_meals_eaten;
	int	i;

	all_meals_eaten = 1;
	i = 0;
	pthread_mutex_lock(&table->last_meal_mutex);
	if (table->nbr_of_meals != -1)
	{
		while (i < table->nbr_of_philos)
		{
			if (table->philos[i].meals_eaten < table->nbr_of_meals)
			{
				all_meals_eaten = 0;
				break ;
			}
			i++;
		}
		if (all_meals_eaten)
		{
			pthread_mutex_lock(&table->death);
			table->died = 1;
			pthread_mutex_unlock(&table->death);
		}
	}
	pthread_mutex_unlock(&table->last_meal_mutex);
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->death);
		if (table->died)
		{
			pthread_mutex_unlock(&table->death);
			break ;
		}
		pthread_mutex_unlock(&table->death);
		i = 0;
		while (i < table->nbr_of_philos)
		{
			if (monitor_death(get_time(), table, i))
				break ;
			i++;
		}
		monitor_meals(table);
		usleep(1000);
	}
	return (NULL);
}

int	has_philosopher_died(t_philo *philo)
{
	t_table	*table;
	int		died;

	table = philo->table;
	pthread_mutex_lock(&table->death);
	died = table->died;
	pthread_mutex_unlock(&table->death);
	return (died);
}
