/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 04:00:07 by btan              #+#    #+#             */
/*   Updated: 2024/04/29 05:57:35 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*r_init(int argc, char **argv)
{
	int		no;
	t_rules	*rules;

	no = ft_atol(argv[1]);
	rules = ft_calloc(1, sizeof(t_rules));
	rules->no_philo = no;
	rules->ttd = ft_atol(argv[2]);
	rules->tte = ft_atol(argv[3]);
	rules->tts = ft_atol(argv[4]);
	rules->start = time_ms(0);
	rules->forks = ft_calloc(no, sizeof(int));
	rules->mutex = ft_calloc(no, sizeof(pthread_mutex_t));
	pthread_mutex_init(&rules->print, NULL);
	pthread_mutex_init(&rules->status, NULL);
	if (argc >= 6)
		rules->must_eat = ft_atol(argv[5]);
	else
		rules->must_eat = -1;
	while (no--)
		pthread_mutex_init(&rules->mutex[no], NULL);
	return (rules);
}

t_order	*order_init(int id, t_rules *rules)
{
	t_order	*order;
	int		temp;

	order = ft_calloc(1, sizeof(t_order));
	order->first = id;
	if (id == rules->no_philo - 1)
		order->second = 0;
	else
		order->second = id + 1;
	if (id % 2)
	{
		temp = order->first;
		order->first = order->second;
		order->second = temp;
	}
	return (order);
}

t_philo	*p_init(char **argv, t_rules *rules)
{
	int		id;
	t_philo	*philo;
	t_order	*order;

	id = ft_atol(argv[1]);
	philo = ft_calloc(id, sizeof(t_philo));
	while (id--)
	{
		order = order_init(id, rules);
		philo[id].id = id;
		philo[id].no = id + 1;
		philo[id].last_meal = rules->start;
		philo[id].order = order;
		philo[id].rules = rules;
		pthread_mutex_init(&philo[id].mutex, NULL);
	}
	return (philo);
}
