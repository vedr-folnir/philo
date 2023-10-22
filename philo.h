/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:29:51 by hlasota           #+#    #+#             */
/*   Updated: 2023/10/19 16:20:45 by hlasota          ###   ########.fr       */
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

}				t_val;

typedef struct s_philo
{
	int			id;
	int			meals_eat;	
	pthread_t	thread_id;
	long int	last_eat;
	t_val		*vargs;
}							t_philo;

int		ft_atoi(const char *str);
int		digit(int argc, char *argv[]);
int		check_input(int argc, char *argv[], t_val *val);
void	print_instruction(void);
void	*philosophers(void *arg);
int		parse_args(int argc, char **argv, t_val *p);
void	*routine(void *data);
long int	actual_time(void);

#endif