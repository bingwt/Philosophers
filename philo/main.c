/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/06 12:43:34 by btan             ###   ########.fr       */
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
		phils[i].num = i + 1;
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

int	sub_routine(void *args)
{
	t_philo *phils;

	phils = (t_philo *) args;
	phils->state = 3;
	state_change(phils->num, 3);
	while (phils->pp->forks > 0 && phils->forks != 2 \
	&& phils->must_eat && phils->ttd > 0)
	{
		phils->pp->forks--;
		phils->forks++;
		state_change(phils->num, 1);
	}
	if (phils->forks == 2 && phils->must_eat && phils->ttd > 0)
	{
		phils->state = 2;
		state_change(phils->num, 2);
		usleep(phils->pp->tte * 1000);
		phils->must_eat--;
		phils->forks = 0;
		phils->pp->forks += 2;
		phils->ttd = phils->pp->ttd;
	}
	else
	{
		phils->state = 3;
		state_change(phils->num, 3);
	}
	if (phils->ttd <= 0)
	{
		phils->state = 4;
		state_change(phils->num, 4);
		exit(0);
	}
	phils->state = 0;
	state_change(phils->num, 0);
	phils->ttd--;
	return (1);
}

// void *death_timer_thread(void *args)
// {
// 	t_philo *phils = (t_philo *)args;
	
// 	while (phils->ttd > 0)
// 	{
// 		usleep(1000);
// 		phils->ttd--;
// 		// death_timer(phils);
// 	}
	
// 	return NULL;
// }

// void routine(t_philo **phils)
// {
// 	int i;
// 	pthread_t phil_thread_id;
// 	pthread_t death_timer_thread_id;
	
// 	i = 0;
// 	while (i < (*phils)->pp->phils)
// 	{
// 		printf("Philosopher number %d\n", (*phils)[i].num);
// 		sub_routine(&(*phils)[i]);
// 		i++;
// 	}
	
// 	pthread_create(&death_timer_thread_id, NULL, death_timer_thread, (void *)&(*phils)[i]);
	
// 	i = 0;
// 	while (i < (*phils)->pp->phils)
// 	{
// 		pthread_join(phils[i]->thread, NULL);
// 		i++;
// 	}
	
// 	pthread_join(death_timer_thread_id, NULL);
// }

void routine(t_philo **phils)
{
	int i;
	// int *thread_return;

	i = 0;
	// thread_return = ft_calloc((*phils)->pp->phils + 1, sizeof(int));
	while (i < (*phils)->pp->phils)
	{
		printf("Philosopher number %d\n", (*phils)[i].num);
		// thread_return[i] = pthread_create(&phils[i]->thread, NULL, (void *) sub_routine, (void *)&(*phils)[i]);
		sub_routine(&(*phils)[i]);
		i++;
	}
	i = 0;
	while (i < (*phils)->pp->phils)
	{
		// pthread_join(phils[i]->thread, NULL);
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_pp	pp;
	t_philo	*phils;

	if (argc != 6)
	{
		printf("Please provide 5 arguments!");
		return (1);
	}
	pp.phils = ft_atoi(argv[1]);
	pp.ttd = ft_atoi(argv[2]);
	pp.tte = ft_atoi(argv[3]);
	pp.tts = ft_atoi(argv[4]);
	pp.must_eat = ft_atoi(argv[5]);
	pp.forks = pp.phils;
	//test(&pp);
	phils = init_phils(&pp);
//	while (phils->num)
//	{
//		check_philo(phils);
//		phils++;
//	}
	//sim(&pp, &phils);
	//sub_routine(&phils[0]);
	while (1)
		routine(&phils);
	//check_philo(phils);
	//test(&pp);
	return (0);
}
