/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:23:09 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/02 10:19:01 by hlasota          ###   ########.fr       */
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
		usleep(time_in_ms *1000);
}

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

int	error(t_val *val)
{
	val->l_philo = malloc(sizeof(t_philo) * val->nb_philo + 1);
	if (!val->l_philo)
	{
		printf("error malloc\n");
		return (-2);
	}
	val->l_fork = malloc(sizeof(t_philo) * val->nb_philo + 1);
	if (!val->l_fork)
	{
		printf("error malloc\n");
		return (-2);
	}
	return (0);
}

void	ft_try_print(char *text, t_philo *philo, long int time, int id)
{

	if (philo->vargs->death != -1)
	{
		printf("%ld %d %s\n", actual_time() - time, id, text);
	}
	return;
}

/*int	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->vargs->l_fork[philo->id - 1]) == 0
		&& pthread_mutex_lock(&philo->vargs->l_fork[philo->id
		% (philo->vargs->nb_philo)]) == 0)
	{
		ft_try_print("has taken a fork", philo, philo->vargs->start, philo->id);
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
	}
	else
	{
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id
			% philo->vargs->nb_philo]);
		return (-1);
	}
	return (0);
}*/

int	ft_eat(t_philo *philo)
{
	while (42)
	{	
		if (philo->last_eat < philo->vargs->time_sleep + 5)
			continue;
		pthread_mutex_lock(&philo->vargs->l_fork[philo->id - 1]);
		ft_try_print("has taken a fork", philo, philo->vargs->start, philo->id);
		pthread_mutex_lock(&philo->vargs->l_fork[philo->id
			% (philo->vargs->nb_philo)]);
		ft_try_print("has taken a fork", philo, philo->vargs->start, philo->id);
		ft_try_print("is eating", philo, philo->vargs->start, philo->id);
		ft_usleep(philo->vargs->time_eat);
		philo->meals_eat++;
		printf("%d  %ld\n", philo->id, actual_time() - philo->last_eat);
		philo->last_eat = actual_time();
		printf("%d  %ld\n", philo->id, actual_time() - philo->last_eat);
		ft_try_print("finish eating", philo, philo->vargs->start, philo->id);
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->vargs->l_fork[philo->id
			% philo->vargs->nb_philo]);
		if (philo->vargs->death == -1)
			return (-1);
		break;
	}
	return (0);
}

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	philo->meals_eat = 0;
	if (philo->id % 2 == 0)
		usleep(philo->vargs->time_eat * 100);
	printf("%ld philo %d vient de se reveiller\n", actual_time() - philo->vargs->start,  philo->id);
	while (42 && philo->meals_eat != philo->vargs->nb_meal)
	{	
		//printf("debut routine %d\n", philo->id);
		if (philo->vargs->death == -1)
			break;
		if (ft_eat(philo) == -1)
			continue;
		ft_try_print("is sleeping", philo, philo->vargs->start, philo->id);
		ft_usleep(philo->vargs->time_sleep);
		if (philo->meals_eat == philo->vargs->nb_meal)
			break;
		ft_try_print("is thinking", philo, philo->vargs->start, philo->id);
	}
	return (0);
}





void	createThreads(t_val *threadData)
{
	int i;
	int result;

	i = 0;
	while (i < threadData->nb_philo)
	{
		threadData->l_philo[i].id = i + 1;
		threadData->l_philo[i].last_eat = actual_time();
		threadData->l_philo[i].vargs = threadData;
		result = pthread_create(&threadData->l_philo[i].thread_id, NULL, routine, &threadData->l_philo[i]);
		if (result)
		{
			printf("Erreur lors de la création du thread %d\n", i);
			return;
		}
		i++;
	}
}

void joinThreads(t_val *threadData)
{
    int i;

    i = 0;
    while (i < threadData->nb_philo)
    {
        pthread_join(threadData->l_philo[i].thread_id, NULL);
        i++;
    }
}

void	ft_death(t_val *val)
{
	int i;

	i = 0;
	while (42)
	{
		if (actual_time() - val->l_philo[i].last_eat >= val->time_die)
		{
			val->death = -1;
			printf("%ld %d has died\n", actual_time() - val->start, i + 1);
			return;
		}
		if (val->l_philo[i].meals_eat == val->nb_meal)
			return;
		i = (i + 1) % val->nb_philo;
	}
}

int	main(int argc, char **argv)
{
	t_val	val;
	int		check_error;
	int		i;

	if (parse_args(argc, argv, &val) != 1)
	{
		printf("wrong args\n");
		return (-1);
	}
	check_error = error(&val);
	if (check_error != 0)
		return (check_error);
	createThreads(&val);
	ft_death(&val);
	joinThreads(&val);
	i = 0;
	/*while (i < val.nb_philo)
	{
		if (pthread_mutex_destroy(&val.l_fork[i]) != 0) {
            perror("Erreur lors de la destruction du mutex");
            // Gérer l'erreur ici, si nécessaire
        } else {
            i++;
        }
	}*/

	return (0);
}
