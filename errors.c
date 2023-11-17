/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:22:30 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/17 16:24:33 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			j = j * -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * j);
}

int	digit(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_val *p)
{
	if ((argc == 5 || argc == 6) && digit(argc, argv))
	{
		p->nb_philo = ft_atoi(argv[1]);
		p->time_die = ft_atoi(argv[2]);
		p->time_eat = ft_atoi(argv[3]);
		p->time_sleep = ft_atoi(argv[4]);
		p->nb_meal = -1;
		p->death = 0;
		if (argc == 6)
			p->nb_meal = ft_atoi(argv[5]);
		if (p->nb_philo <= 0 || p->time_die <= 0 || p->time_eat <= 0 \
			|| p->time_sleep <= 0)
			return (0);
		p->start = actual_time();
		return (1);
	}
	return (0);
}

int	init_data_race_mutex(t_val *val)
{
	int	i;

	i = 0;
	while (i < 8)
		if (pthread_mutex_init(&val->change_val[i++], NULL) != 0)
			return (-3);
	return (0);
}

int	error(t_val *val)
{
	int	i;

	val->l_philo = malloc(sizeof(t_philo) * val->nb_philo + 1);
	if (!val->l_philo)
	{
		printf("error malloc\n");
		return (-2);
	}
	val->l_fork = malloc(sizeof(pthread_mutex_t) * val->nb_philo + 1);
	if (!val->l_fork)
	{
		printf("error malloc\n");
		return (-2);
	}
	i = 0;
	while (i < val->nb_philo)
	{
		if (pthread_mutex_init(&val->l_fork[i], NULL) != 0)
			return (-3);
		i++;
	}
	return (init_data_race_mutex(val));
}
