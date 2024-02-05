/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/05 18:40:42 by btan             ###   ########.fr       */
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
		phils[i].forks = 0;
		phils[i].pp = pp;
		i++;
	}
	return (phils);
}

void	sim(t_pp *pp, t_philo **phils)
{
	int	i;

	i = 0;
	while (i < pp->phils)
	{
		i++;
		while ((*phils)->ttd != 0)
		{
			usleep(1000);
			(*phils)->ttd--;
			check_philo(*phils);
		}
		printf("Dieded");
	}
}

void	sub_routine(t_philo *phils)
{
	phils->state = 3;
	state_change(phils->pos, 3);
	while (phils->pp->forks > 0 && phils->forks != 2 && phils->must_eat && phils->ttd > 0)
	{
		phils->pp->forks--;
		phils->forks++;
		state_change(phils->pos, 1);
	}	
	if (phils->forks == 2 && phils->must_eat && phils->ttd > 0)
	{
		phils->ttd = phils->pp->ttd;
		phils->state = 2;
		state_change(phils->pos, 2);
	}
	else
	{
		phils->state = 3;
		state_change(phils->pos, 3);
	}
	while (phils->forks > 0 && phils->ttd > 0)
	{
		phils->forks--;
		phils->pp->forks++;
	}
	if (phils->ttd <= 0)
		phils->state = 4;
	phils->state = 0;
}

void	*routine(t_philo **phils)
{
	int	i;
	int	*thread_return;

	i = 0;
	thread_return = ft_calloc((*phils)->pp->phils + 1, sizeof(int));
	while (i < (*phils)->pp->phils)
		thread_return[i] = pthread_create(&phils[i]->thread, NULL, sub_routine, phils);
	i = 0;
	while (i < (*phils)->pp->phils)
		pthread_join(thread[i], NULL);
	return (NULL);
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
	pp.forks = pp.phils + 1;
	//test(&pp);
	phils = init_phils(&pp);
//	while (phils->pos)
//	{
//		check_philo(phils);
//		phils++;
//	}
	//sim(&pp, &phils);
	//sub_routine(&phils[0]);
	routine(&phils);
	//check_philo(phils);
	//test(&pp);
	return (0);
}
