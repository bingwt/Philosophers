/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 02:21:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(long milliseconds)
{
	long	start;

	start = time_ms(0);
	while ((time_ms(0) - start) < milliseconds)
		usleep(500);
}

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->status);
	if (philo->rules->philo_no)
	{
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->status);
	pthread_mutex_lock(&philo->rules->meal[philo->id]);
	if ((philo->action != EAT || philo->status == FULL) \
		&& time_ms(0) - philo->last_meal >= philo->rules->ttd)
	{
		pthread_mutex_unlock(&philo->rules->meal[philo->id]);
		if (philo->status == ALIVE)
			print_action(philo, "died");
		philo->status = DEAD;
		pthread_mutex_lock(&philo->rules->status);
		philo->rules->philo_no = philo->no;
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->meal[philo->id]);
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
	free(rules->meal);
	free(rules->mutex);
	free(rules);
}
