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

/*void	check_args(int argc, char **argv)
{

}*/
void	free_all(t_table *table)
{
	if (table != NULL)
	{
		if (table->philos != NULL)
			free(table->philos);
		free(table);
	}
}

void	erfre(t_table *table,int i)
{
	int	j;

	j = 0;
	if (table != NULL && table->forks != NULL)
	{
		while (j < i)
		{
			pthread_mutex_destroy(&table->forks[j]);
			j++;
		}
		pthread_mutex_destroy(&table->print);
	}
	free_all(table);
	exit(EXIT_FAILURE);
}