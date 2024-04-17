/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 01:19:50 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	p_action((t_philo *) philo, TAKE);
	p_action((t_philo *) philo, EAT);
	p_action((t_philo *) philo, SLEEP);
	p_action((t_philo *) philo, THINK);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;
	int		i;

	if (argc < 5)
	{
		printf("Please provide at least 4 argument!!");
		return (1);
	}
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	i = 0;
	while (i < rules->no_philo)
		routine((void *)&philo[i++]);
	return (0);
}
