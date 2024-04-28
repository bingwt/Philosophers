/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/29 05:26:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo 	*philo;
	t_rules 	*rules;
	t_status	status;

	philo = (t_philo *) p;
	rules = philo->rules;
	status = philo->status;
	while (status == ALIVE)
	{
		p_action(philo, rules);
		status = philo->status;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philo;
	pthread_t	*thread;
	int		i;

	if (check_input(argc, argv))
		return (1);
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	thread = ft_calloc(rules->no_philo, sizeof(pthread_t));
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_create(&thread[i], NULL, routine, &philo[i]);
		i++;
	}
	while (1)
		if (monitor(philo, rules))
			break ;
	i = 0;
	while (i < rules->no_philo)
		pthread_join(thread[i++], NULL);
	free_philo(philo, rules);
	free(thread);
	return (0);
}
