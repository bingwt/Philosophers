/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:14:12 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 01:44:26 by btan             ###   ########.fr       */
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
	THINK,
	EAT,
	SLEEP,
	TAKE,
	RETURN
}	e_action;

typedef enum e_status
{
	ALIVE,
	DEAD
}	e_status;

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
	int			ate;
	time_t		last_meal;
	time_t		dead;
	e_action	action;
	e_status	status;
	pthread_t	thread;
}	t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
time_t	time_ms(time_t start);

#endif
