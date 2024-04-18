/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:37 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 16:14:09 by btan             ###   ########.fr       */
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
	DEAD
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
	long		last_meal;
	long		ts;
	t_action	action;
	t_status	status;
	t_order		*order;
	t_rules		*rules;
	pthread_t	thread_id;
}	t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
long	time_ms(time_t start);
t_rules	*r_init(int argc, char **argv);
t_philo	*p_init(char **argv, t_rules *rules);
int		p_action(t_philo *philo);

#endif
