/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/16 18:39:03 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pp	*init_pp(char **argv)
{
	t_pp			*pp;

	pp = ft_calloc(1, sizeof(t_pp));
	pp->start = timestamp_in_ms(0);
	pp->phils = ft_atoi(argv[1]);
	pp->ttd = ft_atoi(argv[2]);
	pp->tte = ft_atoi(argv[3]);
	pp->tts = ft_atoi(argv[4]);
	pp->must_eat = ft_atoi(argv[5]);
	return (pp);
}

t_philo	*init_phils(t_pp *pp)
{
	t_philo	*phils;
	int		i;

	phils = ft_calloc(pp->phils + 1, sizeof(t_philo));
	i = 0;
	while (i < pp->phils)
	{
		phils[i].num = i + 1;
		phils[i].forks = 1;
		phils[i].eaten = 0;
		phils[i].last_meal = 0;
		phils[i].pp = pp;
		phils[i].state = 0;
		phils[i].next = NULL;
		phils[i].prev = NULL;
		philo_action(0, &phils[i], (t_action) THINK);
		i++;
	}
	return (phils);
}

void	link_phils(t_philo *phils)
{
	int	i;

	i = 0;
	while (phils[i].num)
	{
		if (phils[i + 1].num)
			phils[i].next = &phils[i + 1];
		if (i > 0)
			phils[i].prev = &phils[i - 1];
		i++;
	}
	phils[0].prev = &phils[i - 1];
	phils[i - 1].next = &phils[0];
}

int	sub_routine(void *args)
{
	t_philo			*phils;
	time_t			start;

	phils = (t_philo *) args;
	start = phils->pp->start;
	if (phils->next->forks == 1)
		philo_action(timestamp_in_ms(phils->pp->start), phils, (t_action) TAKE);
	if (phils->forks == 2)
	{
		philo_action(timestamp_in_ms(start), phils, (t_action) EAT);
		philo_action(timestamp_in_ms(start), phils, (t_action) RETURN);
		philo_action(timestamp_in_ms(start), phils, (t_action) SLEEP);
	}

	return (0);
}

void	routine(t_philo *phils)
{
	int	i;
	int	*threads;

	i = 0;
	threads = ft_calloc(phils->pp->phils + 1, sizeof(int));
	while (phils->pp->phils)
	{
		threads[i] = pthread_create(&phils[i].thread, NULL, (void *) sub_routine,\
		(void *) &phils[i]);
		i++;
	}
	i = 0;
	while (i < phils->pp->phils)
		pthread_join(phils[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_pp			*pp;
	t_philo			*phils;

	if (argc != 6)
	{
		printf("Please provide 5 arguments!");
		return (1);
	}
	pp = init_pp(argv);
	pthread_mutex_init(&pp->mutex, NULL);
	phils = init_phils(pp);
	link_phils(phils);
	sub_routine((void *) &phils[0]);
//	while (1)
//	{
//		sub_routine();
//	}
}
