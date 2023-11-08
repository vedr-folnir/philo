/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:23:09 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/08 12:54:02 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_eat(t_philo *philo)
{
	while (42)
	{
		if (philo->last_eat < philo->vargs->time_sleep + 5)
			continue ;
		pthread_mutex_lock(&philo->vargs->l_fork[philo->id - 1]);
		ft_try_print("has taken a fork", philo, philo->vargs->start, philo->id);
		pthread_mutex_lock(&philo->vargs->l_fork[philo->id
			% (philo->vargs->nb_philo)]);
		ft_try_print("has taken a fork", philo, philo->vargs->start, philo->id);
		ft_try_print("is eating", philo, philo->vargs->start, philo->id);
		ft_usleep(philo->vargs->time_eat);
		philo->meals_eat++;
		philo->last_eat = actual_time();
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id
			% philo->vargs->nb_philo]);
		if (philo->vargs->death == -1)
			return (-1);
		break ;
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(philo->vargs->time_eat * 100);
	while (42 && philo->meals_eat != philo->vargs->nb_meal)
	{
		if (philo->vargs->death == -1)
			break ;
		if (ft_eat(philo) == -1)
			continue ;
		ft_try_print("is sleeping", philo, philo->vargs->start, philo->id);
		ft_usleep(philo->vargs->time_sleep);
		if (philo->meals_eat == philo->vargs->nb_meal)
			break ;
		ft_try_print("is thinking", philo, philo->vargs->start, philo->id);
	}
	return (0);
}

int	leak_destroyer(t_val	val)
{
	int		i;

	i = 0;
	while (i < val.nb_philo)
	{
		if (pthread_mutex_destroy(&val.l_fork[i]) != 0)
			return (-1);
		else
			i++;
	}
	free(val.l_fork);
	free(val.l_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_val	val;
	int		check_error;

	if (parse_args(argc, argv, &val) != 1)
	{
		printf("wrong args\n");
		return (-1);
	}
	if (val.nb_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(val.time_die);
		printf("%ld 1 has die\n", val.time_die);
		return (0);
	}
	check_error = error(&val);
	if (check_error != 0)
		return (check_error);
	create_threads(&val);
	ft_death(&val);
	join_threads(&val);
	return (leak_destroyer(val));
}
