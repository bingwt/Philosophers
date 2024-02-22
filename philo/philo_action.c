/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 02:04:36 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 03:00:37 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action == (e_action) THINK)
		return ;
	seat->philos[no].action = (e_action) THINK;
	printf("%ld %d is thinking\n", ms, no);
	return ;
}

void	philo_eat(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action == (e_action) EAT)
		return ;
	seat->philos[no].action = (e_action) EAT;
	printf("%ld %d is eating\n", ms, no);
	usleep(seat->rules->eat * 1000);
	return ;
}

void	philo_sleep(time_t ms, int no, t_seat *seat)
{
	if (seat->philos[no].action == (e_action) SLEEP)
		return ;
	seat->philos[no].action = (e_action) SLEEP;
	printf("%ld %d is sleeping\n", ms, no);
	usleep(seat->rules->slp * 1000);
	return ;
}
