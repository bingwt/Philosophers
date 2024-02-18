/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:06:30 by btan              #+#    #+#             */
/*   Updated: 2024/02/18 11:57:59 by btan             ###   ########.fr       */
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

typedef enum s_action
{
	SLEEP,
	THINK,
	EAT,
	TAKE,
	RETURN
}	t_action;

typedef enum s_status
{
	DEAD,
	ALIVE
}	t_status;

typedef struct s_philo_params
{
	int				ttd;
	int				tte;
	int				tts;
	int				phils;
	int				must_eat;
	time_t			start;
	pthread_mutex_t	mutex;
}	t_pp;

typedef struct s_philo
{
	int				num;
	int				forks;
	int				eaten;
	time_t			last_meal;
	t_pp			*pp;
	t_action		state;
	pthread_t		thread;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
time_t	timestamp_in_ms(time_t start);
int		check_phils(t_philo *phils);

void	philo_action(time_t timestamp, t_philo *philo, t_action action);
void	philo_status(time_t timestamp, t_philo *philo, t_status status);

#endif
