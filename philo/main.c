/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:24:54 by btan              #+#    #+#             */
/*   Updated: 2024/03/06 11:25:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philo			*philos;
	t_seat			*seats;
	int				no_philos;

	rules = init_rules(argc, argv);
	no_philos = rules->no_philos;
	philos = ft_calloc(no_philos, sizeof(t_philo));
	if (!philos)
		return (1);
	seats = init_seats(rules, philos);
	while (!philo_status(seats))
		routine(seats);
	return (0);
}
