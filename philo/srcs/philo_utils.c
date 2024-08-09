/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:38:48 by msiitone          #+#    #+#             */
/*   Updated: 2024/06/11 17:39:05 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_checkneg(int neg)
{
	if (0 < neg)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	result;
	long int	oldn;

	i = 0;
	result = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		oldn = result;
		result = result * 10 + (str[i] - 48);
		if (oldn > result)
			return (ft_checkneg(neg));
		i++;
	}
	return (result * neg);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	print_message(const char *str, t_philo *philo)
{
	t_table	*table;
	int		current_time;

	table = philo->table;
	pthread_mutex_lock(&table->print);
	current_time = get_time() - table->start;
	printf("%d %d %s\n", current_time, philo->id, str);
	pthread_mutex_unlock(&table->print);
	return (0);
}
