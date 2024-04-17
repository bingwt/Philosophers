/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:00:02 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 00:03:36 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fork()
{

}
int	p_action(t_philo *philo, t_action action)
{
	int	id;
	int	timestamp;

	id = philo->id;
	timestamp = 0;
	printf("Action: %d\n", action);
	printf("%d ", timestamp);
	if (action == THINK)
		printf("%d is thinking\n", philo->no);
	if (action == TAKE)
	{
		pthread_mutex_lock(&philo->rules->mutex[id]);
		philo->rules->forks[id] = 1;
		pthread_mutex_lock(&philo->rules->mutex[id + 1]);
		philo->rules->forks[id + 1] = 1;
		printf("%d has taken a fork\n", philo->no);
	}
	if (action == EAT)
	{
		printf("%d is eating\n", philo->no);
		pthread_mutex_lock(&philo->rules->mutex[id]);
		philo->rules->forks[id] = 0;
		pthread_mutex_lock(&philo->rules->mutex[id + 1]);
		philo->rules->forks[id + 1] = 0;
	}
	if (action == SLEEP)
		printf("%d is sleeping\n", philo->no);
	return (0);
}
