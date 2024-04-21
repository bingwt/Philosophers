/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/22 04:17:23 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(long timestamp, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld %d %s\n", timestamp, philo->no, str);
	pthread_mutex_unlock(&philo->rules->print);
}

int	p_action(t_philo *philo, long timestamp)
{
	int			left;
	int			right;
	t_action	last_action;

	left = philo->order->left;
	right = philo->order->right;
	last_action = philo->action;
	if (last_action == SLEEP)
	{
		philo->action = THINK;
		print_action(timestamp, philo, "is thinking");
	}
	else if (last_action == THINK)
	{
		philo->action = TAKE;
		if (!philo->left)
		{
			pthread_mutex_lock(&philo->rules->mutex[left]);
			philo->rules->forks[left] = 1;
			philo->left = 1;
			print_action(timestamp, philo, "has taken a left fork");
		//	print_action(timestamp, philo, "has taken a fork");
			if (philo->left)
			{
				pthread_mutex_lock(&philo->rules->mutex[right]);
				philo->rules->forks[right] = 1;
				philo->right = 1;
				print_action(timestamp, philo, "has taken a right fork");
			//	print_action(timestamp, philo, "has taken a fork");
			}
		}
		if (!(philo->left && philo->right))
			{
				philo->rules->forks[left] = 0;
				philo->left = 0;
				print_action(timestamp, philo, "has return a left fork");
				pthread_mutex_unlock(&philo->rules->mutex[left]);
			}
		}
	else if (last_action == TAKE)
	{
		if (philo->left && philo->right)
		{	
			philo->action = EAT;
			print_action(timestamp, philo, "is eating");
			usleep(philo->rules->tte);
			philo->rules->forks[left] = 0;
			philo->left = 0;
			print_action(timestamp, philo, "has return a left fork");
			pthread_mutex_unlock(&philo->rules->mutex[left]);
			philo->rules->forks[right] = 0;
			philo->right = 0;
			print_action(timestamp, philo, "has return a right fork");
			pthread_mutex_unlock(&philo->rules->mutex[right]);
			philo->last_meal = time_ms(0);
			philo->meals++;
		}
	}
	else if (last_action == EAT)
	{
		philo->action = SLEEP;
		print_action(timestamp, philo, "is sleeping");
		usleep(philo->rules->tts);
	}
	return (0);
}
