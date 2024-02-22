/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 02:04:36 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 04:53:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action != (t_action) SLEEP)
		return ;
	seat->philos[no].action = (t_action) THINK;
	printf("%ld %d is thinking\n", ms, no);
}

void	philo_eat(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action != (t_action) THINK)
		return ;
	if (seat->philos[no].forks != 2)
		return ;
	seat->philos[no].action = (t_action) EAT;
	printf("%ld %d is eating\n", ms, no);
	usleep(seat->rules->eat * 1000);
	seat->philos[no].forks -= 2; 
}

void	philo_sleep(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action != (t_action) EAT)
		return ;
	seat->philos[no].action = (t_action) SLEEP;
	printf("%ld %d is sleeping\n", ms, no);
	usleep(seat->rules->slp * 1000);
}

static void	philo_take(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action != (t_action) THINK)
		return ;
	printf("%ld %d has taken a fork\n", ms, no);
	seat->philos[no].forks++;
}

void	philo_forks(time_t ms, int no, t_seat *seat)
{
	int	left;
	int	right;

	left = seat->no - 1;
	right = seat->no;
	if (seat->no == seat->rules->no_philos)
		right = 0;
	pthread_mutex_lock(&seat->forks[left]);
	philo_take(ms, no, seat);
	pthread_mutex_lock(&seat->forks[right]);
	philo_take(ms, no, seat);
	philo_eat(ms, no, seat);
	pthread_mutex_unlock(&seat->forks[left]);
	pthread_mutex_unlock(&seat->forks[right]);
}

