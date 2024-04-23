/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:20:22 by btan              #+#    #+#             */
/*   Updated: 2024/04/24 01:49:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	handle_error(t_error error)
{
	printf("Error: ");
	if (error == NOT_ENOUGH_ARGS)
		printf("Please provide at least 4 arguments!!!\n");
	else if (error == TOO_MANY_ARGS)
		printf("Please provide no more than 5 arguments!!!\n");
	else if (error == NAN)
		printf("Please provide only numeric int inputs!!!\n");
	return (1);
}

int	check_input(int argc, char **argv)
{
	int		i;
	char	*str;

	if (argc < 5)
		return (handle_error(NOT_ENOUGH_ARGS));
	if (argc > 6)
		return (handle_error(TOO_MANY_ARGS));
	i = 0;
	while (i++ < argc)
	{
		while (argv[i])
		{
			str = argv[i];
			while (*str)
			{
				if (!ft_isdigit(*(str++)))
					return (handle_error(NAN));
			}
			if (ft_atol(argv[i]) < -2147483648 \
				|| ft_atol(argv[i]) > 2147483647)
				return (handle_error(NAN));
			i++;
		}
	}
	return (0);
}

void	*routine(void *philo)
{
	t_status	status;
	int			must_eat;
	int			meals;

	status = ((t_philo *) philo)->status;
	must_eat = ((t_philo *) philo)->rules->must_eat;
	meals = ((t_philo *) philo)->meals;
	if (((t_philo *) philo)->no % 2 == 0)
		philo_sleep(500);
	while (status == ALIVE && meals != must_eat)
	{
		pthread_mutex_lock(&((t_philo *) philo)->rules->status);
		status = ((t_philo *) philo)->status;
		if (((t_philo *) philo)->rules->philo_no)
		{
			pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
			break ;
		}
		pthread_mutex_unlock(&((t_philo *) philo)->rules->status);
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

	if (check_input(argc, argv))
		return (1);
	rules = r_init(argc, argv);
	philo = p_init(argv, rules);
	i = 0;
	while (i < rules->no_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
		i++;
	}
	i = 0;
	while (1)
		if (monitor(philo, rules))
			break ;
	while (i < rules->no_philo)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < rules->no_philo)
		pthread_mutex_destroy(&philo->rules->mutex[i++]);
	free_philo(philo, rules);
	return (0);
}
