/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 15:18:45 by btan             ###   ########.fr       */
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

void	philo_sleep(long milliseconds)
{
	long	start;

	start = time_ms(0);
	while ((time_ms(0) - start) < milliseconds)
		usleep(500);
}

int	check_status(t_philo *philo)
{
//	printf("current time: %ld\n", time_ms(0));
//	printf("   last meal: %ld\n", philo->last_meal);
//	printf("        diff: %ld\n", time_ms(philo->last_meal));
	if (time_ms(0) - philo->last_meal >= philo->rules->ttd)
	{
		print_action(philo, "died");
		philo->status = DEAD;
		pthread_mutex_lock(&philo->rules->status);
		philo->rules->philo_no = philo->no;
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	return (0);
}

int	monitor(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->no_philo)
	{
		if (check_status(&philo[i]))
			return (1);
		i++;
	}
	usleep(500);
	return (0);
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
