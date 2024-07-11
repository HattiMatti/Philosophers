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

typedef struct s_philo
{
	int	id;


}	t_philo;

typedef struct s_args
{
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_meals;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				last_meal;
	pthread_t		thread;
	t_args			*args;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_args	args;
}	t_table;

void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(const char *str);




#endif
