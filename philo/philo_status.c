/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/22 20:51:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_philo *philo)
{
	if (time_ms(philo->last_meal) > philo->rules->ttd)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&philo->rules->status);
		philo->rules->philo_no = philo->no;
		pthread_detach(philo->thread_id);
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	return (0);
}

void	philo_do(long ms)
{
	int	i;

	i = ms / 100;
	while (i)
	{
		usleep(100);
		i--;
	}
}
