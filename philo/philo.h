/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:43:02 by btan              #+#    #+#             */
/*   Updated: 2024/03/06 20:21:48 by btan             ###   ########.fr       */
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
}	t_action;

typedef enum e_status
{
	ALIVE,
	DEAD
}	t_status;

typedef struct s_rules
{
	int				no_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philo
{
	int	no;
	int	forks;
	int	action;
	int	status;
}	t_philo;

void	usage(int argc);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
long	time_ms(time_t start);

#endif
