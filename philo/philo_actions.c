/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 02:59:50 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_take(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = TAKE;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	if (check_status(philo))
		return ;
	if (!philo->left)
	{
		if (take_left(philo, order))
			return ;
		if (philo->left)
		{
			if (take_right(philo, order))
				return ;
		}
	}
}

void	alt_take(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = TAKE;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	if (check_status(philo))
		return ;
	if (!philo->right)
	{
		if (alt_right(philo, order))
			return ;
		if (philo->right)
		{
			if (alt_left(philo, order))
				return ;
		}
	}
}

void	p_eat(t_philo *philo, t_order *order)
{
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = EAT;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	print_action(philo, "is eating");
	philo_sleep(philo->rules->tte);
	philo->rules->forks[order->left] = 0;
	philo->left = 0;
	pthread_mutex_unlock(&philo->rules->mutex[order->left]);
	philo->rules->forks[order->right] = 0;
	philo->right = 0;
	pthread_mutex_unlock(&philo->rules->mutex[order->right]);
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->last_meal = time_ms(0);
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	philo->meals++;
	if (philo->meals == philo->rules->must_eat)
	{
		pthread_mutex_lock(&philo->rules->meal[order->left]);
		philo->status = FULL;
		pthread_mutex_unlock(&philo->rules->meal[order->left]);
		pthread_mutex_lock(&philo->rules->print);
		pthread_mutex_unlock(&philo->rules->print);
		return ;
	}
}

void	think_sleep(t_action last_action, t_philo *philo, t_order *order)
{
	if (last_action == SLEEP)
	{
		pthread_mutex_lock(&philo->rules->meal[order->left]);
		philo->action = THINK;
		pthread_mutex_unlock(&philo->rules->meal[order->left]);
		print_action(philo, "is thinking");
	}
	else if (last_action == EAT)
	{
		pthread_mutex_lock(&philo->rules->meal[order->left]);
		philo->action = SLEEP;
		pthread_mutex_unlock(&philo->rules->meal[order->left]);
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
		think_sleep(last_action, philo, order);
	else if (last_action == THINK)
	{
		if (philo->no % 2)
			p_take(philo, order);
		else
			alt_take(philo, order);
	}
	else if (last_action == TAKE)
	{
		if (philo->left && philo->right)
			p_eat(philo, order);
	}
	return (0);
}
