/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:06:30 by btan              #+#    #+#             */
/*   Updated: 2024/02/11 14:55:47 by btan             ###   ########.fr       */
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
	EAT
}	t_action;

typedef enum s_status
{
	DEAD,
	ALIVE
}	t_status;

typedef struct s_philo_params
{
	time_t			start;
	int				phils;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	int				forks;
	int				unique_eats;
	pthread_mutex_t	mutex;
}	t_pp;

typedef struct s_philosopher
{
	int			num;
	t_action	state;
	int			ttd;
	int			must_eat;
	int				has_eaten;
	int			forks;
	pthread_t	thread;
	t_pp		*pp;
}	t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		available_forks(t_philo *philo);
int		check_philo(t_philo *philo);
void	test(t_pp *pp);

void	philo_action(t_philo *philo, t_action action);
void	philo_status(t_philo *philo, t_status status);

#endif
