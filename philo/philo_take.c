/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 02:43:52 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 22:17:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->mutex[order->left]);
	philo->rules->forks[order->left] = 1;
	philo->left = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	take_right(t_philo *philo, t_order *order)
{
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
		return (1);
	}
	if (philo->rules->no_philo < 2)
	{
		philo_sleep(philo->rules->ttd);
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->mutex[order->right]);
	philo->rules->forks[order->right] = 1;
	philo->right = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
		pthread_mutex_unlock(&philo->rules->mutex[order->right]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	alt_right(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->mutex[order->right]);
	philo->rules->forks[order->right] = 1;
	philo->right = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->right]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	alt_left(t_philo *philo, t_order *order)
{
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->right]);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->mutex[order->left]);
	philo->rules->forks[order->left] = 1;
	philo->left = 1;
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->rules->mutex[order->right]);
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}
