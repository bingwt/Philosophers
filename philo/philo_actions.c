/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 01:32:43 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	check_fork()
//{
//
//}
int	p_action(t_philo *philo, t_action action)
{
	int	left;
	int	right;
	int	*forks;
	int	timestamp;

	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	timestamp = 0;
//	printf("Action: %d\n", action);
	printf("%d ", timestamp);
	if (action == THINK)
		printf("%d is thinking\n", philo->no);
	if (action == TAKE && !(forks[left] && forks[right]))
	{
		pthread_mutex_lock(&philo->rules->mutex[left]);
		forks[left] = 1;
//		pthread_mutex_lock(&philo->rules->mutex[right]);
		forks[right] = 1;
		printf("%d has taken a fork\n", philo->no);
	}
	if (action == EAT && (forks[left] && forks[right]))
	{
		printf("%d is eating\n", philo->no);
		usleep(philo->rules->tte);
		pthread_mutex_unlock(&philo->rules->mutex[left]);
		forks[left] = 0;
//		pthread_mutex_unlock(&philo->rules->mutex[right]);
		forks[right] = 0;
	}
	if (action == SLEEP)
	{
		printf("%d is sleeping\n", philo->no);
		usleep(philo->rules->tts);
	}
	return (0);
}
