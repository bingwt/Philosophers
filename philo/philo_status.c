/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/29 06:03:51 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->meals == rules->must_eat)
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	if (time_ms(philo->last_meal) > rules->ttd)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&rules->status);
		rules->philo_no = philo->no;
		pthread_mutex_unlock(&rules->status);
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

int	monitor(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->no_philo)
	{
		if (check_status(&philo[i], rules))
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
	pthread_mutex_destroy(&philo->rules->print);
	pthread_mutex_destroy(&philo->rules->status);
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&rules->mutex[i++]);
	}
	free(philo);
	free(rules->forks);
	free(rules->mutex);
	free(rules);
}
