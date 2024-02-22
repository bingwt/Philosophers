/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:07:29 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 03:12:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_rules	*init_rules(int argc, char **argv)
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

static int	philo_status(t_seat *seat)
{
	int	i;

	i = 0;
	while (i < seat->rules->no_philos)
	{
		if (seat->philos[i].status)
		{
			printf("%ld %d died\n", seat->philos[i].dead, i + 1);
			return ((e_status) DEAD);
		}
		i++;
	}
	return ((e_status) ALIVE);
}

static void	sub(t_seat *seat)
{
	time_t	start;

	start = seat->rules->start;
	philo_think(time_ms(start), seat->no, seat);
}

static void	routine(t_seat *seat)
{
	int	i;

	i = 0;
	while (i < seat->rules->no_philos)
	{
		seat->no = i + 1;
		pthread_create(&seat->philos[i].thread, NULL, \
		(void *) &sub, (void *) seat);
	}
	i = 0;
	while (i < seat->rules->no_philos)
		pthread_join(seat->philos[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_seat	seat;

	seat.rules = init_rules(argc, argv);
	seat.philos = ft_calloc(seat.rules->no_philos, sizeof(t_philo));
	while (!philo_status(&seat))
		routine(&seat);
}
