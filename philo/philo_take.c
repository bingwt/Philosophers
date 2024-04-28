/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 02:43:52 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 18:18:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_first(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->mutex[order->first]);
	philo->rules->forks[order->first] = 1;
	philo->left = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->first]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	take_second(t_philo *philo, t_order *order)
{
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->first]);
		return (1);
	}
	if (philo->rules->no_philo < 2)
	{
		philo_sleep(philo->rules->ttd);
		pthread_mutex_unlock(&philo->rules->mutex[order->first]);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->mutex[order->second]);
	philo->rules->forks[order->second] = 1;
	philo->right = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->first]);
		pthread_mutex_unlock(&philo->rules->mutex[order->second]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}