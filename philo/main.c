/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 03:11:57 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	int		id;
	int		meals;
	int		must_eat;
	//long	timestamp;

	id = ((t_philo *) philo)->id;
	meals = ((t_philo *) philo)->meals;
	must_eat = ((t_philo *) philo)->rules->must_eat;
	while (meals < must_eat && !(id % 2))
	{
		p_action((t_philo *) philo, TAKE);
		p_action((t_philo *) philo, EAT);
		p_action((t_philo *) philo, SLEEP);
		p_action((t_philo *) philo, THINK);
		meals = ((t_philo *) philo)->meals;
	}
	//timestamp = time_ms(((t_philo *) philo)->rules->start);
	//printf("%ld %d finished %d meals\n", timestamp, ((t_philo *) philo)->no, must_eat);
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;
	int		i;

	if (argc < 5)
	{
		printf("Please provide at least 4 argument!!");
		return (1);
	}
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	i = 0;
	if (argc == 7 && argv[6][0] == 's')
	{
		while (i < rules->no_philo)
			routine((void *)&philo[i++]);
		return (0);
	}
	while (i < rules->no_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, routine, (void *) &philo[i]);
		i++;
	}
	i = 0;
	while (i < rules->no_philo)
		pthread_join(philo[i++].thread_id, NULL);
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_rules	*rules;
//	t_philo	*philo;
//	int		i;
//
//	if (argc < 5)
//	{
//		printf("Please provide at least 4 argument!!");
//		return (1);
//	}
//	rules = r_init(argc, argv);
//	philo = p_init(argv, rules);
//	i = 0;
//	while (i < rules->no_philo)
//	{
//		pthread_create(&philo[i].thread_id, NULL, routine, (void *) &philo[i]);
//		i++;
//	}
//	i = 0;
//	while (i < rules->no_philo)
//		pthread_join(philo[i++].thread_id, NULL);
//	return (0);
//}
//
//int	main(int argc, char **argv)
//{
//	t_rules	*rules;
//	t_philo	*philo;
//	int		i;
//
//	if (argc < 5)
//	{
//		printf("Please provide at least 4 argument!!");
//		return (1);
//	}
//	rules = r_init(argc, argv);
//	philo = p_init(argv, rules);
//	i = 0;
//	while (i < rules->no_philo)
//		routine((void *)&philo[i++]);
//	return (0);
//}
