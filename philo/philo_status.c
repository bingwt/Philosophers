/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 02:32:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_ms(long start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}

int	check_status(t_philo *philo)
{
	if (time_ms(philo->last_meal) >= philo->rules->ttd)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&philo->rules->status);
		philo->rules->philo_no = philo->no;
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	return (0);
}

void	philo_sleep(long ms)
{
	int	i;

	i = ms / 1500;
	while (i--)
		usleep(1500);
}

void	free_philo(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->no_philo)
	{
		free(philo[i].order);
		i++;
	}
	free(philo);
	free(rules->forks);
	free(rules->mutex);
	free(rules);
}
