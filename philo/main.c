/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/25 04:10:46 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_status	status;
	int			must_eat;
	int			meals;

	status = ((t_philo *) philo)->status;
	must_eat = ((t_philo *) philo)->rules->must_eat;
	meals = ((t_philo *) philo)->meals;
	while (status == ALIVE && meals != must_eat)
	{
		pthread_mutex_lock(&((t_philo *) philo)->rules->status);
		status = ((t_philo *) philo)->status;
		if (((t_philo *) philo)->rules->philo_no)
		{
			pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
			break ;
		}
		pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
		p_action((t_philo *) philo);
		meals = ((t_philo *) philo)->meals;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;
	int		i;

	if (check_input(argc, argv))
		return (1);
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
		i++;
	}
	i = 0;
	while (1)
		if (monitor(philo, rules))
			break ;
	while (i < rules->no_philo)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	free_philo(philo, rules);
	return (0);
}
