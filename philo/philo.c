/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:07:29 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 02:01:07 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_rules	*init_rules(int	argc, char **argv)
{
	t_rules	*rules;

	rules = ft_calloc(ft_atoi(argv[1]), sizeof(t_rules));
	if (!rules)
		return (NULL);
	if (argc != 6)
		rules->must_eat = -1;
	else
		rules->must_eat = ft_atoi(argv[5]);
	rules->no_philos = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->slp = ft_atoi(argv[4]);
	rules->start = time_ms(0);
	return (rules);
}

static int	philo_status(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->no_philos)
	{
		if (philos[i].status)
		{
			printf("%ld %d died\n", philos[i].dead, i + 1);
			return ((e_status) DEAD);
		}
		i++;
	}
	return ((e_status) ALIVE);
}

void	test(t_rules *rules, t_philo *philos)
{
	time_t	start;

	printf("e_action: %d\n", (e_action) EAT);
	start = time_ms(0);
	printf("time_ms: %ld\n", start);
	usleep(10 * 1000);
	printf("time_ms: %ld\n", time_ms(start));
	philo_status(rules, philos);
	usleep(10 * 1000);
	philos[0].status = (e_status) DEAD;
	philos[0].dead = time_ms(start);
	philo_status(rules, philos);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philos;

	rules = init_rules(argc, argv);
	philos = ft_calloc(rules->no_philos, sizeof(t_philo));
	test(rules, philos);
}

