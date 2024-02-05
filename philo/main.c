/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/05 13:09:12 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_phils(t_pp *pp)
{
	t_philo *phils;
	int		i;
	
	phils = ft_calloc(pp->phils + 1, sizeof(t_philo));
	i = 0;
	while (i < pp->phils)
	{
		phils[i].pos = i + 1;
		phils[i].state = 0;
		phils[i].ttd = pp->ttd;
		phils[i].must_eat = pp->must_eat;
		i++;
	}
	return (phils);
}

void	sim(t_philo **phils)
{
	while ((*phils)->ttd != 0)
	{
		usleep(1000);
		(*phils)->ttd--;
		check_philo(*phils);
	}
	printf("Dieded");
}

int	main(int argc, char **argv)
{
	t_pp	pp;
	t_philo	*phils;

	if (argc != 5)
	{
		printf("Please provide 5 arguments!");
		return (1);
	}
	pp.phils = ft_atoi(argv[1]);
	pp.ttd = ft_atoi(argv[2]);
	pp.tte = ft_atoi(argv[3]);
	pp.tts = ft_atoi(argv[4]);
	//pp.must_eat = ft_atoi(argv[5]);
	pp.forks = pp.phils;
	test(&pp);
	phils = init_phils(&pp);
//	while (phils->pos)
//	{
//		check_philo(phils);
//		phils++;
//	}
	sim(&phils);
	return (0);
}
