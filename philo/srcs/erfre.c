/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erfre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:15 by msiitone          #+#    #+#             */
/*   Updated: 2024/06/11 17:37:35 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_table *table)
{
	if (table != NULL)
	{
		if (table->philos != NULL)
			free(table->philos);
		if (table->forks != NULL)
			free(table->forks);
	}
}

void	free_end(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->last_meal_mutex);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death);
	free_all(table);
	return ;
}
