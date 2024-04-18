/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 03:15:59 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *philo, long timestamp)
{
	int	action;

	action = philo->action;
	if (action == THINK)
	{
		printf("%ld ", timestamp);
		printf("%d is thinking\n", philo->no);
	}
}

void	p_take(t_philo *philo, long timestamp)
{
	t_action	action;
	int			left;
	int			right;
	int			*forks;

	action = philo->action;
	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	if (action == TAKE && !(forks[left] && forks[right]))
	{
		pthread_mutex_lock(&philo->rules->mutex[left]);
		forks[left] = 1;
		printf("%ld %d has taken a fork\n", timestamp, philo->no);
	}
	if (action == TAKE && !(!forks[left] && forks[right]))
	{
		pthread_mutex_lock(&philo->rules->mutex[right]);
		forks[right] = 1;
		printf("%ld %d has taken a fork\n", timestamp, philo->no);
	}
}

void	p_eat(t_philo *philo, long timestamp)
{
	t_action	action;
	int			left;
	int			right;
	int			*forks;

	action = philo->action;
	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	if (action == EAT && (forks[left] && forks[right]))
	{
		printf("%ld ", timestamp);
		printf("%d is eating\n", philo->no);
		usleep(philo->rules->tte);
		philo->ts = time_ms(philo->rules->start);
		pthread_mutex_unlock(&philo->rules->mutex[left]);
		forks[left] = 0;
		pthread_mutex_unlock(&philo->rules->mutex[right]);
		forks[right] = 0;
		philo->meals++;
	}
}

void	p_sleep(t_philo *philo, long timestamp)
{
	int	action;

	action = philo->action;
	if (action == SLEEP)
	{
		printf("%ld ", timestamp);
		printf("%d is sleeping\n", philo->no);
		usleep(philo->rules->tts);
		philo->ts = time_ms(philo->rules->start);
	}
}

int	p_action(t_philo *philo, t_action action)
{
//	long	start;
	long	timestamp;

	philo->action = action;
//	start = philo->rules->start;
	timestamp = time_ms(philo->rules->start);
	p_take(philo, timestamp);
	p_eat(philo, timestamp);
	p_sleep(philo, timestamp);
	p_think(philo, timestamp);
	return (0);
}
