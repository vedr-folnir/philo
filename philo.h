/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:29:51 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/17 16:39:23 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_val {
	int				nb_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				nb_meal;
	long int		start;
	pthread_mutex_t	*l_fork;
	int				death;
	struct s_philo	*l_philo;
	pthread_mutex_t	change_val[8];
}				t_val;

typedef struct s_philo
{
	int			id;
	int			meals_eat;	
	pthread_t	thread_id;
	long int	last_eat;
	t_val		*vargs;
}							t_philo;

int			ft_atoi(const char *str);
int			digit(int argc, char *argv[]);
int			check_input(int argc, char *argv[], t_val *val);
void		print_instruction(void);
void		*philosophers(void *arg);
int			parse_args(int argc, char **argv, t_val *p);
void		*routine(void *data);
long int	actual_time(void);
void		create_threads(t_val *threadData);
void		join_threads(t_val *threadData);
void		ft_death(t_val *val);
void		ft_usleep(long int time_in_ms);
void		ft_try_print(char *text, t_philo *philo, long int time, int id);
int			error(t_val *val);
int			get_death(t_val *val);
long int	get_last_eat(t_philo *philo);
int			get_meals(t_philo *philo);

#endif
