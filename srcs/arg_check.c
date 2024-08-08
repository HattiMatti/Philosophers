/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:17:04 by msiitone          #+#    #+#             */
/*   Updated: 2024/08/08 03:17:53 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int is_number(char arg)
{
	if (arg >= '0' && arg <= '9')
		return (0);
	else
		return (1);
}

int	is_pos(int argc, char **argv)
{
	int i;

	i = 1;
	if (ft_atoi(argv[1]) > 200)
		return (1);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc) 
	{
		j = 0;
		if (argv[i][0] == '\0')
			return 1;
		while (argv[i][j] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (is_number(argv[i][j]) != 0)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}
