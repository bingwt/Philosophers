/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:39 by btan              #+#    #+#             */
/*   Updated: 2024/03/06 20:48:37 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->no_philos = ft_atoi(argv[1]);
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	if (argc == 5)
		rules->must_eat = -1;
	else
		rules->must_eat = ft_atoi(argv[5]);
	rules->forks = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_mutex_t));
	return (rules);
}

t_philo	*init_philo(int argc)
{
	t_philo	*philo;

	philo = ft_calloc(argc, sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (argc--)
		philo[argc].no = argc + 1;
	return (philo);
}

int	main(int argc, char **argv)
{
	int		i;
	t_rules	*rules;
	t_philo	*philo;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		usage(argc);
		return (1);
	}
	rules = init_rules(argc, argv);
	if (!rules)
		return (1);
	philo = init_philo(argc);
	if (!philo)
		return (1);
	return (0);
}
