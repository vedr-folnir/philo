/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:52 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/17 16:38:41 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*philosophers(void *arg)
{
	t_val		*val;
	long int	time[2];

	time[0] = actual_time();
	ft_usleep(40);
	time[1] = actual_time();
	printf("%ld\n", time[1] - time[0]);
	val = (t_val *)arg;
	return (0);
}

void	create_threads(t_val *threadData)
{
	int	i;
	int	result;

	i = 0;
	while (i < threadData->nb_philo)
	{
		threadData->l_philo[i].id = i + 1;
		threadData->l_philo[i].meals_eat = 0;
		threadData->l_philo[i].last_eat = actual_time();
		threadData->l_philo[i].vargs = threadData;
		result = pthread_create(&threadData->l_philo[i].thread_id,
				NULL, routine, &threadData->l_philo[i]);
		if (result)
		{
			printf("Erreur lors de la création du thread %d\n", i);
			return ;
		}
		i++;
	}
}

void	join_threads(t_val *threadData)
{
	int	i;

	i = 0;
	while (i < threadData->nb_philo)
	{
		pthread_join(threadData->l_philo[i].thread_id, NULL);
		i++;
	}
}

void	ft_death(t_val *val)
{
	int	i;

	i = 0;
	while (42)
	{
		if (actual_time() - get_last_eat(&val->l_philo[i]) >= val->time_die)
		{
			pthread_mutex_lock(&val->change_val[0]);
			val->death = -1;
			pthread_mutex_unlock(&val->change_val[0]);
			printf("%ld %d has died\n", actual_time() - val->start, i + 1);
			return ;
		}
		pthread_mutex_lock(&val->change_val[7]);
		if (get_meals(&val->l_philo[i]) == val->nb_meal)
		{
			pthread_mutex_unlock(&val->change_val[7]);
			return ;
		}
		pthread_mutex_unlock(&val->change_val[7]);
		i = (i + 1) % val->nb_philo;
	}
}
