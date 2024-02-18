/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/18 15:05:17 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*init_phils(char **argv)
{
	t_philo	*phils;
	int		i;

	phils = ft_calloc(ft_atoi(argv[1]) + 1, sizeof(t_philo));
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		phils[i].num = i + 1;
		phils[i].ttd = ft_atoi(argv[2]);
		phils[i].tte = ft_atoi(argv[3]);
		phils[i].ttd = ft_atoi(argv[4]);
		phils[i].must_eat = ft_atoi(argv[5]);
		phils[i].total = ft_atoi(argv[1]);
		phils[i].forks = 1;
		phils[i].last_meal = 0;
		phils[i].start = timestamp_in_ms(0);
		phils[i].state = 0;
		phils[i].next = NULL;
		phils[i].prev = NULL;
		philo_action(0, &phils[i], (t_action) THINK);
		i++;
	}
	link_phils(phils);
	return (phils);
}

int	sub_routine(void *args)
{
	t_philo			*phils;
	time_t			start;

	phils = (t_philo *) args;
	start = phils->start;
	philo_action(timestamp_in_ms(phils->start), phils, (t_action) THINK);
	if (phils->next->forks == 1)
		philo_action(timestamp_in_ms(phils->start), phils, (t_action) TAKE);
	if (phils->forks == 2 && phils->must_eat)
	{
		philo_action(timestamp_in_ms(start), phils, (t_action) EAT);
		philo_action(timestamp_in_ms(start), phils, (t_action) RETURN);
		philo_action(timestamp_in_ms(start), phils, (t_action) SLEEP);
	}
	else
		philo_action(timestamp_in_ms(start), phils, (t_action) RETURN);

	return (0);
}

void	routine(t_philo *phils)
{
	int	i;
	int	*threads;

	i = 0;
	threads = ft_calloc(phils->total + 1, sizeof(int));
	while (phils[i].num)
	{
		threads[i] = pthread_create(&phils[i].thread, NULL, (void *) sub_routine,\
		(void *) &phils[i]);
		i++;
	}
	i = 0;
	while (i < phils->total)
		pthread_join(phils[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*phils;

	if (argc != 6)
	{
		printf("Please provide 5 arguments!\n");
		return (1);
	}
	phils = init_phils(argv);
//	sub_routine((void *) &phils[0]);
	while (1)
	{
		routine(phils);
		if (!check_phils(phils))
		{
			return (0);
		}
	}
}
