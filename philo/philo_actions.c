/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 02:14:37 by btan             ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = TAKE;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	if (check_status(philo))
			return ;
	if (!philo->left)
	{
		pthread_mutex_lock(&philo->rules->mutex[order->left]);
		philo->rules->forks[order->left] = 1;
		philo->left = 1;
		if (check_status(philo))
		{
			pthread_mutex_unlock(&philo->rules->mutex[order->left]);
			return ;
		}
		print_action(philo, "has taken a left fork");
		if (philo->left)
		{
			if (check_status(philo))
			{
				pthread_mutex_unlock(&philo->rules->mutex[order->left]);
				return ;
			}
			if (philo->rules->no_philo < 2)
			{
				philo_sleep(philo->rules->ttd);
				pthread_mutex_unlock(&philo->rules->mutex[order->left]);
				return ;
			}
			if (check_status(philo))
			{
				pthread_mutex_unlock(&philo->rules->mutex[order->left]);
				return ;
			}
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
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = TAKE;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	if (check_status(philo))
			return ;
	if (!philo->right)
	{
		pthread_mutex_lock(&philo->rules->mutex[order->right]);
		philo->rules->forks[order->right] = 1;
		philo->right = 1;
		if (check_status(philo))
		{
			pthread_mutex_unlock(&philo->rules->mutex[order->right]);
			return ;
		}
		print_action(philo, "has taken a right fork");
		if (philo->right)
		{
			if (check_status(philo))
			{
				pthread_mutex_unlock(&philo->rules->mutex[order->right]);
				return ;
			}
			pthread_mutex_lock(&philo->rules->mutex[order->left]);
			philo->rules->forks[order->left] = 1;
			philo->left = 1;
			if (check_status(philo))
			{
				pthread_mutex_unlock(&philo->rules->mutex[order->right]);
				pthread_mutex_unlock(&philo->rules->mutex[order->left]);
				return ;
			}
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
	if (check_status(philo))
			return ;
	pthread_mutex_lock(&philo->rules->meal[order->left]);
	philo->action = EAT;
	pthread_mutex_unlock(&philo->rules->meal[order->left]);
	print_action(philo, "is eating");
	philo_sleep(philo->rules->tte);
	philo->rules->forks[order->left] = 0;
	philo->left = 0;
	//print_action(philo, "has return a left fork");
	pthread_mutex_unlock(&philo->rules->mutex[order->left]);
	philo->rules->forks[order->right] = 0;
	philo->right = 0;
	//print_action(philo, "has return a right fork");
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
		printf("%d ate %d times\n", philo->no, philo->meals);
		pthread_mutex_unlock(&philo->rules->print);
		return ;
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
	if (last_action == SLEEP)
	{
		pthread_mutex_lock(&philo->rules->meal[order->left]);
		philo->action = THINK;
		pthread_mutex_unlock(&philo->rules->meal[order->left]);
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
		pthread_mutex_lock(&philo->rules->meal[order->left]);
		philo->action = SLEEP;
		pthread_mutex_unlock(&philo->rules->meal[order->left]);
		print_action(philo, "is sleeping");
		philo_sleep(philo->rules->tts);
	}
	return (0);
}
