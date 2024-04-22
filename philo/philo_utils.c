/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:14 by btan              #+#    #+#             */
/*   Updated: 2024/04/23 02:52:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *) s;
	while (n > 0)
		ptr[(n--) - 1] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, nmemb * size);
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
	rules->mutex = ft_calloc(no, sizeof(pthread_mutex_t));
	if (argc >= 6)
		rules->must_eat = ft_atol(argv[5]);
	else
		rules->must_eat = -1;
	while (no--)
		pthread_mutex_init(&rules->mutex[no], NULL);
	return (rules);
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
		order = ft_calloc(1, sizeof(t_order));
		order->left = id;
		if (id == rules->no_philo - 1)
			order->right = 0;
		else
			order->right = id + 1;
		philo[id].id = id;
		philo[id].no = id + 1;
		philo[id].last_meal = rules->start;
		philo[id].tod = rules->start + rules->ttd;
		philo[id].order = order;
		philo[id].rules = rules;
	}
	return (philo);
}
