/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:37 by btan              #+#    #+#             */
/*   Updated: 2024/04/15 20:32:27 by btan             ###   ########.fr       */
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

typedef enum	e_action
{
	THINK,
	TAKE,
	EAT,
	SLEEP
}	t_action;

typedef enum	e_state
{
	ALIVE,
	DEAD
}	t_state;


typedef struct	s_rules
{
	int				no_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	int				*forks;
	pthread_mutex_t	*mutex;
}	t_rules;

typedef struct	s_philo
{
	int			no;
	int			meals;
	t_state		status;
	pthread_t	thread_id;
}	t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);

#endif
