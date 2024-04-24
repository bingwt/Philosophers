/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 22:32:03 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld %d %s\n", time_ms(philo->rules->start), philo->no, str);
	pthread_mutex_unlock(&philo->rules->print);
}

void	philo_sleep(long milliseconds)
{
	long	start;

	start = time_ms(0);
	while ((time_ms(0) - start) < milliseconds)
		usleep(500);
}

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->status);
	if (philo->rules->philo_no)
	{
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	pthread_mutex_lock(&philo->rules->meal[philo->id]);
	if ((philo->action != EAT || philo->status == FULL) \
		&& time_ms(0) - philo->last_meal >= philo->rules->ttd)
	{
		if (philo->status == ALIVE)
			print_action(philo, "died");
		philo->status = DEAD;
		pthread_mutex_unlock(&philo->rules->meal[philo->id]);
		philo->rules->philo_no = philo->no;
		pthread_mutex_unlock(&philo->rules->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->meal[philo->id]);
	pthread_mutex_unlock(&philo->rules->status);
	return (0);
}

int	monitor(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->no_philo)
	{
		if (check_status(&philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_philo(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->no_philo)
	{
		free(philo[i].order);
		i++;
	}
	pthread_mutex_destroy(&philo->rules->print);
	pthread_mutex_destroy(&philo->rules->status);
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_mutex_destroy(&philo->rules->meal[i++]);
		pthread_mutex_destroy(&philo->rules->mutex[i++]);
	}
	free(philo);
	free(rules->forks);
	free(rules->meal);
	free(rules->mutex);
	free(rules);
}
