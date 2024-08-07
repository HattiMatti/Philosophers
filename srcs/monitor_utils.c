#include "../includes/philo.h"

int	monitor_death(int current_time, t_table *table, int i)
{
	pthread_mutex_lock(&table->death);
	if ((current_time - table->philos[i].last_meal) > table->time_to_die)
	{
		print_message("died", &table->philos[i]);
		table->died = 1;
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

void	monitor_meals(t_table *table, int i)
{
	int	all_meals_eaten;

	all_meals_eaten = 1;
	if (table->nbr_of_meals != -1)
	{
		if (table->philos[i].meals_eaten < table->nbr_of_meals)
		{
			all_meals_eaten = 0;
		}
		if (all_meals_eaten)
			table->died = 1;
	}
}
