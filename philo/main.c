/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/14 14:37:24 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pp	*init_pp(char **argv)
{
	struct timeval	timestamp;
	t_pp			*pp;

	gettimeofday(&timestamp, NULL);
	pp = ft_calloc(1, sizeof(t_pp));
	pp->start = timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000;
	pp->phils = ft_atoi(argv[1]);
	pp->ttd = ft_atoi(argv[2]);
	pp->tte = ft_atoi(argv[3]);
	pp->tts = ft_atoi(argv[4]);
	pp->must_eat = ft_atoi(argv[5]);
	pp->forks = pp->phils;
	pp->unique_eats = 0;
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
		phils[i].state = 0;
		phils[i].ttd = pp->ttd;
		phils[i].must_eat = pp->must_eat;
		phils[i].forks = 0;
		phils[i].has_eaten = 0;
		phils[i].pp = pp;
		philo_action(&phils[i], (t_action) THINK);
		i++;
	}
	return (phils);
}

int	sub_routine(void *args)
{
	t_philo	*phils;

	phils = (t_philo *) args;
	philo_action(phils, (t_action) THINK);
	while (available_forks(phils) > 0 && phils->forks != 2 \
	&& phils->must_eat && phils->ttd > 0)
	{
		pthread_mutex_lock(&phils->pp->mutex);
		phils->pp->forks--;
		phils->forks++;
		pthread_mutex_unlock(&phils->pp->mutex);
		// philo_action(phils, (t_action) TAKE);
	}
	if (phils->forks == 2 && phils->must_eat && phils->ttd > 0)
	{
		philo_action(phils, (t_action) EAT);
		philo_action(phils, (t_action) SLEEP);
	}
	else
		philo_action(phils, (t_action) THINK);
	while (phils->forks > 0)
	{
		pthread_mutex_lock(&phils->pp->mutex);
		phils->forks--;
		phils->pp->forks++;
		pthread_mutex_unlock(&phils->pp->mutex);
		// philo_action(phils, (t_action) RETURN);
	}
	if (phils->ttd <= 0)
		philo_status(phils, (t_status) DEAD);
	return (1);
}

void	routine(t_philo **phils)
{
	int	i;
	int	*threads;

	i = 0;
	threads = ft_calloc((*phils)->pp->phils + 1, sizeof(int));
	while (i < (*phils)->pp->phils)
	{
		threads[i] = pthread_create(&(*phils)[i].thread, NULL, \
		(void *) sub_routine, (void *)&(*phils)[i]);
		i++;
	}
	i = 0;
	while (i < (*phils)->pp->phils)
		pthread_join((*phils)[i++].thread, NULL);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_pp			*pp;
	t_philo			*phils;
	int				philo;

	if (argc != 6)
	{
		printf("Please provide 5 arguments!");
		return (1);
	}
	pp = init_pp(argv);
	pthread_mutex_init(&pp->mutex, NULL);
	phils = init_phils(pp);
	while (1)
	{
		routine(&phils);
		philo = 0;
		while (philo < pp->phils)
		{
			if (!check_philo(&phils[philo++]))
			{
				free(phils);
				if (pp)
				{
					free(pp);
					pp = NULL;
				}
				return (0);
			}
			free(phils);
		}
		free(pp);
	}
	return (0);
}
