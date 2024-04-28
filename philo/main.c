/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 14:54:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo *philo;
	t_rules *rules;

	philo = (t_philo *) p;
	rules = philo->rules;
	if (philo->status == ALIVE)
		p_action(philo, rules);
	print_action(philo, "is full");
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
		print_action(&philo[i], "is alive");
		i++;
	}
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
		i++;
	}
//	i = 0;
//	while (1)
//		if (monitor(philo, rules))
//			break ;
	while (i < rules->no_philo)
		pthread_join(philo[i++].thread, NULL);
//	i = 0;
	free_philo(philo, rules);
	return (0);
}
