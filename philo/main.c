/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/16 14:46:51 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*routine(void *philo)
{
	p_action((t_philo *) philo, SLEEP);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;

	if (argc < 5)
	{
		printf("Please provide at least 4 argument!!");
		return (1);
	}
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	printf("%s\n", argv[0]);
	routine((void *)&philo[0]);
	routine((void *)&philo[1]);
	routine((void *)&philo[2]);
	routine((void *)&philo[3]);
	routine((void *)&philo[4]);
	return (0);
}
