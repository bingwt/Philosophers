/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:14:12 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 04:01:20 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_action
{
	SLEEP,
	EAT,
	THINK,
	TAKE,
	RETURN
}	t_action;

typedef enum e_status
{
	ALIVE,
	DEAD
}	t_status;

typedef struct s_philo_rules
{
	int		must_eat;
	int		no_philos;
	time_t	die;
	time_t	eat;
	time_t	slp;
	time_t	start;
}	t_rules;

typedef struct s_philo
{
	int			forks;
	int			ate;
	time_t		last_meal;
	time_t		dead;
	t_action	action;
	t_status	status;
	pthread_t	thread;
}	t_philo;

typedef struct s_seat
{
	int				no;
	t_rules			*rules;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_seat;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
time_t	time_ms(time_t start);

void	philo_think(time_t ms, int no, t_seat *seat);
void	philo_eat(time_t ms, int no, t_seat *seat);
void	philo_sleep(time_t ms, int no, t_seat *seat);
void	philo_forks(time_t ms, int no, t_seat *seat);

#endif
