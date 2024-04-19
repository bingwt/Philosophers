/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/19 13:25:54 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *philo, long timestamp)
{
	printf("%ld %d is thinking\n", timestamp, philo->no);
	philo->action = THINK;
}

void	take_fork(t_philo *philo, int *forks, int hand, long timestamp)
{
	forks[hand] = 1;
	printf("%ld %d has taken a fork\n", timestamp, philo->no);
	philo->action = TAKE;
}

void	p_take(t_philo *philo, long timestamp)
{
	int			left;
	int			right;
	int			*forks;

	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	pthread_mutex_lock(&philo->rules->mutex[left]);
	if (!forks[left])
	{
		take_fork(philo, forks, left, timestamp);
		pthread_mutex_lock(&philo->rules->mutex[right]);
		if (!forks[right])
			take_fork(philo, forks, right, timestamp);
		else
		{
			forks[left] = 0;
			pthread_mutex_unlock(&philo->rules->mutex[left]);
			philo->action = THINK;
		}
	}
}

void	p_eat(t_philo *philo, long timestamp)
{
	int			left;
	int			right;
	int			*forks;

	if (time_ms(philo->last_meal) > philo->rules->ttd)
	{
//		printf("%ld - last\n", philo->last_meal);
//		printf("%ld - start\n", philo->rules->start);
//		printf("%ld - ded\n", philo->last_meal - philo->rules->start);
		printf("%ld %d died\n", time_ms(philo->last_meal), philo->no);
	}
	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	if (forks[left] && forks[right])
	{
		printf("%ld ", timestamp);
		printf("%d is eating\n", philo->no);
		usleep(philo->rules->tte);
		philo->ts = time_ms(philo->rules->start);
		forks[left] = 0;
		forks[right] = 0;
		pthread_mutex_unlock(&philo->rules->mutex[left]);
		pthread_mutex_unlock(&philo->rules->mutex[right]);
		philo->meals++;
		philo->last_meal = time_ms(0) - philo->last_meal;
		philo->action = EAT;
	}
}

void	p_sleep(t_philo *philo, long timestamp)
{

	printf("%ld ", timestamp);
	printf("%d is sleeping\n", philo->no);
	usleep(philo->rules->tts);
	philo->ts = time_ms(philo->rules->start);
	philo->action = SLEEP;
}

int	p_action(t_philo *philo)
{
	t_action	last_action;
	long		timestamp;

	last_action = philo->action;
	timestamp = time_ms(philo->rules->start);
	if (last_action == SLEEP)
		p_think(philo, timestamp);
	else if (last_action == THINK)
		p_take(philo, timestamp);
	else if (last_action == TAKE)
		p_eat(philo, timestamp);
	else if (last_action == EAT)
		p_sleep(philo, timestamp);
	return (0);
}
