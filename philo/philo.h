/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:37 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 03:34:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_error
{
	NOT_ENOUGH_ARGS,
	TOO_MANY_ARGS,
	NAN,
}	t_error;

typedef enum e_action
{
	THINK,
	TAKE,
	EAT,
	SLEEP
}	t_action;

typedef enum e_status
{
	ALIVE,
	DEAD,
	FULL
}	t_status;

typedef struct s_rules
{
	int				no_philo;
	long			ttd;
	long			tte;
	long			tts;
	long			start;
	int				must_eat;
	int				*forks;
	int				philo_no;
	pthread_mutex_t	print;
	pthread_mutex_t	status;
	pthread_mutex_t	*mutex;
}	t_rules;

typedef struct s_order
{
	int	left;
	int	right;
}	t_order;

typedef struct s_philo
{
	int			id;
	int			no;
	int			meals;
	int			left;
	int			right;
	long		last_meal;
	long		tod;
	long		ts;
	t_action	action;
	t_status	status;
	t_order		*order;
	t_rules		*rules;
	pthread_t	thread;
}	t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atol(const char *str);
long	time_ms(long start);
t_rules	*r_init(int argc, char **argv);
t_philo	*p_init(char **argv, t_rules *rules);
int		check_status(t_philo *philo);
void	philo_sleep(long ms);
void	free_philo(t_philo *philo, t_rules *rules);
void	print_action(t_philo *philo, char *str);
int		p_action(t_philo *philo);

#endif
