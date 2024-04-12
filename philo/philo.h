/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:37 by btan              #+#    #+#             */
/*   Updated: 2024/04/12 16:58:18 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <phtread.h>

typedef enum	e_action
{
	THINK,
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
	int	no_philos;
	int	ttd;
	int	tte;
	int	tts;
	int	must_eat;
}	t_rules;

typedef stuct	s_philo
{
	int			no;
	int			ate;
	t_state		ALIVE;
	pthread_t	id;
}

#endif
