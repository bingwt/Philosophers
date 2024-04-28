/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 03:49:13 by btan              #+#    #+#             */
/*   Updated: 2024/04/29 06:01:15 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_think(t_philo *philo)
{
	philo->action = THINK;
	print_action(philo, "is thinking");
	return (1);
}

int	p_take(t_philo *philo, t_order *order, t_rules *rules)
{
	philo->action = TAKE;
	pthread_mutex_lock(&rules->mutex[order->first]);
	philo->first = 1;
	print_action(philo, "has taken a fork");
	if (philo->first)
	{
		pthread_mutex_lock(&rules->mutex[order->second]);
		philo->second = 1;
		print_action(philo, "has taken a fork");
	}
	return (1);
}

int	p_eat(t_philo *philo, t_rules *rules)
{
	philo->action = EAT;
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->mutex);
	philo->meals++;
	if (philo->meals == rules->must_eat)
		philo->status = FULL;
	philo->last_meal = time_ms(0);
	pthread_mutex_unlock(&philo->mutex);
	philo_sleep(rules->tte);
	return (1);
}

int	p_sleep(t_philo *philo, t_rules *rules)
{
	t_order	*order;

	order = philo->order;
	philo->action = SLEEP;
	print_action(philo, "is sleeping");
	philo->first = 0;
	pthread_mutex_unlock(&rules->mutex[order->first]);
	philo->second = 0;
	pthread_mutex_unlock(&rules->mutex[order->second]);
	philo_sleep(rules->tts);
	return (1);
}

int	p_action(t_philo *philo, t_rules *rules)
{
	t_order	*order;

	order = philo->order;
	if (philo->action == THINK)
		return (p_take(philo, order, rules));
	if (philo->first && philo->second && philo->action == TAKE)
		return (p_eat(philo, rules));
	else if (philo->first && !philo->second)
	{
		philo->first = 0;
		pthread_mutex_unlock(&rules->mutex[order->first]);
		philo->action = THINK;
	}
	if (philo->action == EAT)
		return (p_sleep(philo, rules));
	if (philo->action == SLEEP)
		return (p_think(philo));
	return (0);
}
