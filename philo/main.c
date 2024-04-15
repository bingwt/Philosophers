/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/15 21:34:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*r_init(int argc, char **argv)
{
	int		no;
	t_rules	*rules;

	no = ft_atoi(argv[1]);
	rules = ft_calloc(1, sizeof(t_rules));
	rules->no_philos = no;
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	rules->forks = ft_calloc(no, sizeof(int));
	rules->mutex = ft_calloc(no, sizeof(pthread_mutex_t));
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	while (no--)
		pthread_mutex_init(&rules->mutex[no], NULL);
	return (rules);
}

t_philo	*p_init(char **argv)
{
	int		no;
	t_philo	*philos;

	no = ft_atoi(argv[1]);
	philos = ft_calloc(no, sizeof(t_philo));
	while (no--)
		philos[no].no = no + 1;
	return (philos);
}

int	p_action(t_philo *philo, t_action action)
{
	int	timestamp;

	timestamp = 0;
	printf("Action: %d\n", action);
	printf("%d ", timestamp);
	if (action == THINK)
		printf("%d is thinking\n", philo->no);
	if (action == TAKE)
		printf("%d has taken a fork\n", philo->no);
	if (action == EAT)
		printf("%d is eating\n", philo->no);
	if (action == SLEEP)
		printf("%d is sleeping\n", philo->no);
	return (0);
}

void	*routine(void *philo)
{
	p_action((t_philo *) philo, SLEEP);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philos;

	if (argc < 5)
	{
		printf("Please provide at least 4 argument!!");
		return (1);
	}
	rules = r_init(argc, argv);
	philos = p_init(argv);
	printf("%s\n", argv[0]);
	routine((void *)&philos[0]);
	routine((void *)&philos[1]);
	routine((void *)&philos[2]);
	routine((void *)&philos[3]);
	routine((void *)&philos[4]);
	return (0);
}
