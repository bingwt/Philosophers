/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/17 23:58:42 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
