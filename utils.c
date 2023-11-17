/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:40:51 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/17 16:34:54 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms * 1000);
}

void	ft_try_print(char *text, t_philo *philo, long int time, int id)
{
	if (get_death(philo->vargs) != -1)
	{
		printf("%ld %d %s\n", actual_time() - time, id, text);
	}
	return ;
}
