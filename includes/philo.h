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

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				start;
	int				died;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		monitor_thread;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				last_meal;
	int				died;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

void	ft_putstr_fd(char *str, int fd);
void	free_all(t_table *table);
void	erfre(t_table *table, int i);
void	print_message(char *str, t_philo *philo);
void	init_table(t_table *table);
void	init_philos(t_table *table);
void	*philosopher_routine(void *arg);
void	*monitor(void *arg);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	monitor_meals(t_table *table, int i);
int		monitor_death(int current_time, t_table *table, int i);
void	free_end(t_table *table);
int		get_time(void);
int		ft_atoi(const char *str);
int		check_args(int argc, char **argv);
int		is_pos(int argc, char **argv);
int 	is_number(char arg);





#endif
