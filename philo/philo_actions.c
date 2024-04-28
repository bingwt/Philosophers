/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 18:19:08 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_take(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->meal[philo->id]);
	philo->action = TAKE;
	pthread_mutex_unlock(&philo->rules->meal[philo->id]);
	if (check_status(philo))
		return ;
	if (!philo->left)
	{
		if (take_first(philo, order))
			return ;
		if (philo->left)
		{
			if (take_second(philo, order))
				return ;
		}
	}
}

void	p_eat(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->meal[philo->id]);
	philo->action = EAT;
	pthread_mutex_unlock(&philo->rules->meal[philo->id]);
	pthread_mutex_lock(&philo->rules->meal[philo->id]);
	philo->last_meal = time_ms(0);
	pthread_mutex_unlock(&philo->rules->meal[philo->id]);
	print_action(philo, "is eating");
	philo_sleep(philo->rules->tte);
	philo->rules->forks[order->first] = 0;
	philo->left = 0;
	pthread_mutex_unlock(&philo->rules->mutex[order->first]);
	philo->rules->forks[order->second] = 0;
	philo->right = 0;
	pthread_mutex_unlock(&philo->rules->mutex[order->second]);
	philo->meals++;
	if (philo->meals == philo->rules->must_eat)
	{
		pthread_mutex_lock(&philo->rules->meal[philo->id]);
		philo->status = FULL;
		pthread_mutex_unlock(&philo->rules->meal[philo->id]);
		return ;
	}
}

void	think_sleep(t_action last_action, t_philo *philo)
{
	if (last_action == SLEEP)
	{
		pthread_mutex_lock(&philo->rules->meal[philo->id]);
		philo->action = THINK;
		pthread_mutex_unlock(&philo->rules->meal[philo->id]);
		print_action(philo, "is thinking");
	}
	else if (last_action == EAT)
	{
		pthread_mutex_lock(&philo->rules->meal[philo->id]);
		philo->action = SLEEP;
		pthread_mutex_unlock(&philo->rules->meal[philo->id]);
		print_action(philo, "is sleeping");
		philo_sleep(philo->rules->tts);
	}
}

int	p_action(t_philo *philo)
{
	t_order		*order;
	t_action	last_action;

	if (check_status(philo))
		return (1);
	order = philo->order;
	last_action = philo->action;
	if (last_action == SLEEP || last_action == EAT)
		think_sleep(last_action, philo);
	else if (last_action == THINK)
		p_take(philo, order);
	else if (last_action == TAKE)
	{
		if (philo->left && philo->right)
			p_eat(philo, order);
	}
	return (0);
}
