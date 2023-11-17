/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:06:17 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/17 16:38:04 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	get_death(t_val *val)
{
	int	temp;

	pthread_mutex_lock(&val->change_val[0]);
	temp = val->death;
	pthread_mutex_unlock(&val->change_val[0]);
	return (temp);
}

long int	get_last_eat(t_philo *philo)
{
	long int	temp;

	pthread_mutex_lock(&philo->vargs->change_val[1]);
	temp = philo->last_eat;
	pthread_mutex_unlock(&philo->vargs->change_val[1]);
	return (temp);
}

int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->vargs->change_val[4]);
	meals = philo->meals_eat;
	pthread_mutex_unlock(&philo->vargs->change_val[4]);
	return (meals);
}
