/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:39:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/16 18:27:10 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(time_t timestamp, t_philo *philo)
{
	printf("%ld %d is sleeping\n", timestamp, philo->num);
	usleep(philo->pp->tts * 1000);
	philo->state = (t_action) SLEEP;
}

static void	philo_eat(time_t timestamp, t_philo *philo)
{
	printf("%ld %d is eating\n", timestamp, philo->num);
	philo->eaten++;
	usleep(philo->pp->tte * 1000);
	philo->state = (t_action) EAT;
}

static void	philo_fork(time_t timestamp, t_philo *philo, t_action action)
{
	if (action == (t_action) TAKE)
	{
		philo->next->forks--;
		philo->forks++;
		printf("%ld %d has taken a fork\n", timestamp, philo->num);
	}
	if (action == (t_action) RETURN)
	{
		philo->forks--;
		philo->next->forks++;
		printf("%ld %d has returned a fork\n", timestamp, philo->num);
	}
}

void	philo_action(time_t timestamp, t_philo *philo, t_action action)
{
	pthread_mutex_lock(&philo->pp->mutex);
	if (philo->state != action)
	{
		philo->state = action;
		if (action == (t_action) SLEEP)
			philo_sleep(timestamp, philo);
		if (action == (t_action) THINK)
			printf("%ld %d is thinking\n", timestamp, philo->num);
		if (action == (t_action) EAT)
			philo_eat(timestamp, philo);
		else
			philo_fork(timestamp, philo, action);
	}
	pthread_mutex_unlock(&philo->pp->mutex);
}

void	philo_status(time_t timestamp, t_philo *philo, t_status status)
{
	if (status == (t_status) DEAD)
		printf("%ld %d died\n", timestamp, philo->num);
	if (status == (t_status) ALIVE)
		printf("%ld %d is alive\n", timestamp, philo->num);
}