/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:39:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/08 14:26:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(t_philo *philo, t_actions actions)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	if (actions == (t_actions) SLEEP)
	{
		phil->state = 0;
		printf("%ld %d is sleeping\n", timestamp.tv_usec / 1000, phil);
	}
	if (actions == (t_actions) THINK)
	{
		phil->state = 1;
		printf("%ld %d is thinking\n", timestamp.tv_usec / 1000, phil);
	}
	if (actions == (t_actions) EAT)
	{
		phil->state = 2;
		printf("%ld %d is eating\n", timestamp.tv_usec / 1000, phil);
	}
}

void	philo_status(t_philo *philo, t_actions status)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	if (status == (t_status) DEAD)
		printf("%ld %d died\n", timestamp.tv_usec / 1000, phil);
	if (status == (t_status) ALIVE)
		printf("%ld %d is alive\n", timestamp.tv_usec / 1000, phil);
}

int	main()
{
	philo_action(NULL, (t_actions) SLEEP);
	philo_action(NULL, (t_actions) THINK);
	philo_action(NULL, (t_actions) EAT);
}
