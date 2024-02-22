/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:07:29 by btan              #+#    #+#             */
/*   Updated: 2024/02/23 05:38:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_seat	*init_seats(t_rules *rules, t_philo *philos)
{
	pthread_mutex_t	*forks;
	t_seat			*seats;
	int				i;

	forks = ft_calloc(rules->no_philos, sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < rules->no_philos)
		pthread_mutex_init(&forks[i++], NULL);
	seats = ft_calloc(rules->no_philos, sizeof(t_seat));
	if (!seats)
		return (NULL);
	i = 0;
	while (i < rules->no_philos)
	{
		seats[i].no = i + 1;
		seats[i].rules = rules;
		seats[i].philos = philos;
		seats->philos[i].dead = rules->start + rules->die;
		seats[i].forks = forks;
		i++;
	}
	return (seats);
}

static t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = ft_calloc(1, sizeof(t_rules));
	if (!rules)
		return (NULL);
	if (argc != 6)
		rules->must_eat = -1;
	else
		rules->must_eat = ft_atoi(argv[5]);
	rules->no_philos = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->slp = ft_atoi(argv[4]);
	rules->start = time_ms(0);
	return (rules);
}

static int	philo_status(t_seat *seat)
{
	int	i;

	i = 0;
	while (i < seat->rules->no_philos)
	{
		if (seat->philos[i].status)
		{
			printf("%ld %d died\n", seat->philos[i].dead, i + 1);
			return ((t_status) DEAD);
		}
		i++;
	}
	return ((t_status) ALIVE);
}

void	sub(t_seat *seat)
{
	t_rules	*rules;
	t_philo	*philo;
	time_t	start;

	rules = seat->rules;
	philo = &seat->philos[seat->no];
	start = seat->rules->start;
	philo_think(time_ms(start), seat->no, seat);
	if (rules->start - philo->dead < 0)
	{
		//philo->status = (t_status) DEAD;
		//philo->dead = time_ms(start);
		return ;
	}
	philo_forks(time_ms(start), seat->no, seat);
	philo_sleep(time_ms(start), seat->no, seat);
}

static void	routine(t_seat *seat)
{
	int	i;

	i = 0;
	while (i < seat->rules->no_philos)
	{
		seat->no = i + 1;
		pthread_create(&seat->philos[i].thread, NULL, \
		(void *) &sub, (void *) seat);
		i++;
	}
	i = 0;
	while (i < seat->rules->no_philos)
		pthread_join(seat->philos[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philo			*philos;
	t_seat			*seats;
	int				no_philos;

	rules = init_rules(argc, argv);
	no_philos = rules->no_philos;
	philos = ft_calloc(no_philos, sizeof(t_philo));
	if (!philos)
		return (1);
	seats = init_seats(rules, philos);
	while (!philo_status(seats))
		routine(seats);
}
