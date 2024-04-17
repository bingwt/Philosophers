/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 01:53:00 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	check_fork()
//{
//
//}
int	p_action(t_philo *philo, t_action action)
{
	int		left;
	int		right;
	int		*forks;
	long	start;

	left = philo->order->left;
	right = philo->order->right;
	forks = philo->rules->forks;
	start = philo->rules->start;
//	printf("Action: %d\n", action);
	if (action == THINK)
	{
		printf("%ld ", time_ms(0) - start);
		printf("%d is thinking\n", philo->no);
	}
	if (action == TAKE && !(forks[left] && forks[right]))
	{
		printf("%ld ", time_ms(0) - start);
		pthread_mutex_lock(&philo->rules->mutex[left]);
		forks[left] = 1;
		printf("%d has taken a fork\n", philo->no);
	}
	if (action == TAKE && !(!forks[left] && forks[right]))
	{
		printf("%ld ", time_ms(0) - start);
//		pthread_mutex_lock(&philo->rules->mutex[right]);
		forks[right] = 1;
		printf("%d has taken a fork\n", philo->no);
	}
	if (action == EAT && (forks[left] && forks[right]))
	{
		printf("%ld ", time_ms(0) - start);
		printf("%d is eating\n", philo->no);
		usleep(philo->rules->tte);
		pthread_mutex_unlock(&philo->rules->mutex[left]);
		forks[left] = 0;
//		pthread_mutex_unlock(&philo->rules->mutex[right]);
		forks[right] = 0;
		philo->meals++;
	}
	if (action == SLEEP)
	{
		printf("%ld ", time_ms(0) - start);
		printf("%d is sleeping\n", philo->no);
		usleep(philo->rules->tts);
	}
	return (0);
}
