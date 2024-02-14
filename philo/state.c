/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:39:28 by btan              #+#    #+#             */
/*   Updated: 2024/02/12 19:44:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	struct timeval	current;
	time_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = timestamp_in_ms() - philo->pp->start;
	philo->state = (t_action) SLEEP;
	printf("%ld %d is sleeping\n", timestamp, philo->num);
	usleep(philo->pp->tts * 1000);
	if (philo->has_eaten)
	{
		philo->has_eaten = 0;
		philo->ttd = philo->pp->ttd;
	}
}

static void	philo_eat(t_philo *philo)
{
	struct timeval	current;
	time_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = timestamp_in_ms() - philo->pp->start;
	philo->state = (t_action) EAT;
	printf("%ld %d is eating\n", timestamp, philo->num);
	usleep(philo->pp->tte * 1000);
	if (philo->pp->unique_eats < 5 && !philo->has_eaten)
		philo->pp->unique_eats++;
	philo->has_eaten = 1;
	philo->must_eat--;
}

static void	philo_fork(t_philo *philo, t_action action)
{
	if (action == (t_action) TAKE)
	{
		philo->pp->forks--;
		philo->forks++;
	}
	if (action == (t_action) RETURN)
	{
		philo->forks--;
		philo->pp->forks++;
	}
}

void	philo_action(t_philo *philo, t_action action)
{
	struct timeval	current;
	time_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = timestamp_in_ms() - philo->pp->start;
	pthread_mutex_lock(&philo->pp->mutex);
	if (philo->state != action)
	{
		philo->state = action;
		if (action == (t_action) SLEEP)
			philo_sleep(philo);
		if (action == (t_action) THINK)
			printf("%ld %d is thinking\n", timestamp, philo->num);
		if (action == (t_action) EAT)
			philo_eat(philo);
		else
			philo_fork(philo, action);
	}
	pthread_mutex_unlock(&philo->pp->mutex);
}

void	philo_status(t_philo *philo, t_status status)
{
	struct timeval	current;
	time_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = timestamp_in_ms() - philo->pp->start;
	if (status == (t_status) DEAD)
		printf("%ld %d died\n", timestamp, philo->num);
	if (status == (t_status) ALIVE)
		printf("%ld %d is alive\n", timestamp, philo->num);
}
