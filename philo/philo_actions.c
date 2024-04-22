/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 02:30:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld %d %s\n", time_ms(philo->rules->start), philo->no, str);
	pthread_mutex_unlock(&philo->rules->print);
}

void	p_take(t_philo *philo, t_order *order)
{
	philo->action = TAKE;
	if (check_status(philo))
			return ;
	if (!philo->left)
	{
		pthread_mutex_lock(&philo->rules->mutex[order->left]);
		philo->rules->forks[order->left] = 1;
		philo->left = 1;
		print_action(philo, "has taken a left fork");
		if (philo->left)
		{
			pthread_mutex_lock(&philo->rules->mutex[order->right]);
			philo->rules->forks[order->right] = 1;
			philo->right = 1;
			print_action(philo, "has taken a right fork");
		}
	}
	if (!(philo->left || philo->right))
	{
		philo->rules->forks[order->left] = 0;
		philo->left = 0;
		print_action(philo, "has return a left fork");
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
	}
}

void	alt_take(t_philo *philo, t_order *order)
{
	philo->action = TAKE;
	if (!philo->right)
	{
		pthread_mutex_lock(&philo->rules->mutex[order->right]);
		philo->rules->forks[order->right] = 1;
		philo->right = 1;
		print_action(philo, "has taken a right fork");
		if (philo->right)
		{
			pthread_mutex_lock(&philo->rules->mutex[order->left]);
			philo->rules->forks[order->left] = 1;
			philo->left = 1;
			print_action(philo, "has taken a right left");
		}
	}
	if (!(philo->right || philo->left))
	{
		philo->rules->forks[order->right] = 0;
		philo->right = 0;
		print_action(philo, "has return a right fork");
		pthread_mutex_unlock(&philo->rules->mutex[order->left]);
	}
}

void	p_eat(t_philo *philo, t_order *order)
{
	philo->action = EAT;
	print_action(philo, "is eating");
	usleep(philo->rules->tte * 1000);
	philo->rules->forks[order->left] = 0;
	philo->left = 0;
	//print_action(philo, "has return a left fork");
	pthread_mutex_unlock(&philo->rules->mutex[order->left]);
	philo->rules->forks[order->right] = 0;
	philo->right = 0;
	//print_action(philo, "has return a right fork");
	pthread_mutex_unlock(&philo->rules->mutex[order->right]);
	philo->last_meal = time_ms(0);
	philo->meals++;
	if (philo->meals == philo->rules->must_eat)
	{
		philo->status = FULL;
		pthread_mutex_lock(&philo->rules->print);
		printf("%d ate %d times\n", philo->no, philo->meals);
		pthread_mutex_unlock(&philo->rules->print);
	}
}

int	p_action(t_philo *philo)
{
	t_order		*order;
	t_action	last_action;

	order = philo->order;
	last_action = philo->action;
	if (last_action == SLEEP)
	{
		philo->action = THINK;
		print_action(philo, "is thinking");
	}
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
	else if (last_action == EAT)
	{
		philo->action = SLEEP;
		print_action(philo, "is sleeping");
		usleep(philo->rules->tts * 1000);
	}
	return (0);
}
