/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:06:30 by btan              #+#    #+#             */
/*   Updated: 2024/02/08 14:16:58 by btan             ###   ########.fr       */
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

typedef enum s_actions
{
	SLEEP,
	THINK,
	EAT
}	t_actions;

typedef enum s_status
{
	DEAD,
	ALIVE
}	t_status;

typedef struct s_philo_params
{
	int				phils;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	int				forks;
	pthread_mutex_t	mutex;
}	t_pp;

typedef struct s_philosopher
{
	int			num;
	int			state;
	int			ttd;
	int			must_eat;
	int			forks;
	pthread_t	thread;
	pthread_t	death_thread;
	t_pp		*pp;
}	t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);

void	philo_actions(t_philo *philo, t_actions actions);
void	philo_status(t_philo *philo, t_status status);

void	check_philo(t_philo *philo);
void	test(t_pp *pp);

#endif
