/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 03:49:13 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 14:57:00 by btan             ###   ########.fr       */
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
	pthread_mutex_lock(&rules->mutex[order->first]);
	philo->first = 1;
	rules->forks[philo->id] = 1;
	print_action(philo, "has taken a fork");
	return (1);
}

int	p_eat(t_philo *philo, t_rules *rules)
{
	print_action(philo, "is eating");
	philo_sleep(rules->tte);
	return (1);
}

int	p_sleep(t_philo *philo, t_rules *rules)
{
	print_action(philo, "is sleeping");
	philo_sleep(rules->tts);
	return (1);
}

int	p_action(t_philo *philo, t_rules *rules)
{
	t_order	*order;

	order = philo->order;
	philo->status = FULL;
	return (0);
	if (philo->action == THINK)
		p_take(philo, order, rules);
	if (philo->first && philo->second && philo->action == TAKE)
		return (p_eat(philo, rules));
	if (philo->action == EAT)
		return (p_sleep(philo, rules));
	if (philo->action == SLEEP)
		return (p_think(philo));
	return (0);
}
