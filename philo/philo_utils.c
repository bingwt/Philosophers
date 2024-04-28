/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:14 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 18:16:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	size_t	n;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	n = nmemb * size;
	while (--n)
		arr[n] = '\0';
	return ((void *) arr);
}

long	ft_atol(const char *str)
{
	long	i;
	long	value;
	long	neg;

	i = 0;
	value = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (value * neg);
		value = value * 10 + str[i] - '0';
		i++;
	}
	return (value * neg);
}

t_rules	*r_init(int argc, char **argv)
{
	int		no;
	t_rules	*rules;

	no = ft_atol(argv[1]);
	rules = ft_calloc(1, sizeof(t_rules));
	rules->no_philo = no;
	rules->ttd = ft_atol(argv[2]);
	rules->tte = ft_atol(argv[3]);
	rules->tts = ft_atol(argv[4]);
	rules->start = time_ms(0);
	rules->forks = ft_calloc(no, sizeof(int));
	rules->meal = ft_calloc(no, sizeof(pthread_mutex_t));
	rules->mutex = ft_calloc(no + 1, sizeof(pthread_mutex_t));
	if (argc >= 6)
		rules->must_eat = ft_atol(argv[5]);
	else
		rules->must_eat = -1;
	while (no--)
	{
		pthread_mutex_init(&rules->meal[no], NULL);
		pthread_mutex_init(&rules->mutex[no], NULL);
	}
	return (rules);
}

t_order	*order_init(int id, t_rules *rules)
{
	t_order	*order;
	int		temp;

	order = ft_calloc(1, sizeof(t_order));
	order->first = id;
	if (id == rules->no_philo - 1)
		order->second = 0;
	else
		order->second = id + 1;
	if (id % 2)
	{
		temp = order->first;
		order->first = order->second;
		order->second = temp;
	}
	return (order);
}

t_philo	*p_init(char **argv, t_rules *rules)
{
	int		id;
	t_philo	*philo;
	t_order	*order;

	id = ft_atol(argv[1]);
	philo = ft_calloc(id, sizeof(t_philo));
	while (id--)
	{
		order = order_init(id, rules);
		philo[id].id = id;
		philo[id].no = id + 1;
		philo[id].last_meal = rules->start;
		philo[id].tod = rules->start + rules->ttd;
		philo[id].order = order;
		philo[id].rules = rules;
	}
	return (philo);
}

long	time_ms(long start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}
