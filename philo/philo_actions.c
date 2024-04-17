/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 02:20:18 by btan             ###   ########.fr       */
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
		printf("%ld ", timestamp);
		pthread_mutex_lock(&philo->rules->mutex[left]);
		forks[left] = 1;
		printf("%d has taken a fork\n", philo->no);
	}
	if (action == TAKE && !(!forks[left] && forks[right]))
	{
		printf("%ld ", timestamp);
//		pthread_mutex_lock(&philo->rules->mutex[right]);
		forks[right] = 1;
		printf("%d has taken a fork\n", philo->no);
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
		pthread_mutex_unlock(&philo->rules->mutex[left]);
		forks[left] = 0;
//		pthread_mutex_unlock(&philo->rules->mutex[right]);
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
	}
}

int	p_action(t_philo *philo, t_action action)
{
	long	start;

	philo->action = action;
	start = philo->rules->start;
	p_take(philo, time_ms(0) - start);
	p_eat(philo, time_ms(0) - start);
	p_sleep(philo, time_ms(0) - start);
	p_think(philo, time_ms(0) - start);
	return (0);
}
