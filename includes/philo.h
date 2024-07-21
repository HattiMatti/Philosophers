/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:51 by msiitone          #+#    #+#             */
/*   Updated: 2024/06/11 15:06:21 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	int	nbr_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_meals;
	int	start;
	t_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				last_meal;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

void	ft_putstr_fd(char *str, int fd);
void	free_all(t_table *table);
void	erfre(t_table *table,int i);
void	print_message(char *str, t_table *table);
int		get_time(void);
int		ft_atoi(const char *str);






#endif
