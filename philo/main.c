/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 01:58:15 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_status	status;
	int			must_eat;
	int			meals;

	status = ((t_philo *) philo)->status;
	must_eat = ((t_philo *) philo)->rules->must_eat;
	meals = ((t_philo *) philo)->meals;
//	if (((t_philo *) philo)->no % 2 == 1)
//		usleep(1);
	while (status == ALIVE && meals != must_eat)
	{
		pthread_mutex_lock(&((t_philo *) philo)->rules->status);
		if (((t_philo *) philo)->rules->philo_no)
		{
			pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
		//	pthread_detach(((t_philo *) philo)->thread_id);
			break ;
		}
		pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
		if (check_status((t_philo *) philo))
			break ;
		p_action((t_philo *) philo);
		meals = ((t_philo *) philo)->meals;
	}
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
//	while (1)
//	{
//		pthread_mutex_lock(&rules->status);
//		if (rules->philo_no)
//		{
//			pthread_mutex_unlock(&rules->status);
//			return (0);
//		}
//		pthread_mutex_unlock(&rules->status);
//	}
	i = 0;
	while (i < rules->no_philo)
		pthread_join(philo[i++].thread_id, NULL);
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_mutex_destroy(&philo->rules->mutex[i]);
		i++;
	}
	free_philo(philo, rules);
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
