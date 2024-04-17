/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:14 by btan              #+#    #+#             */
/*   Updated: 2024/04/18 01:19:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;

	arr = malloc(nmemb * size);
	while (--size)
		arr[size] = 0;
	return ((void *) arr);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	val;
	int	neg;

	i = 0;
	val = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg = -neg;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (val * neg);
		val = val * 10 + str[i++] - '0';
	}
	return (val * neg);
}

t_rules	*r_init(int argc, char **argv)
{
	int		no;
	t_rules	*rules;

	no = ft_atoi(argv[1]);
	rules = ft_calloc(1, sizeof(t_rules));
	rules->no_philo = no;
	rules->ttd = ft_atoi(argv[2]) * 1000;
	rules->tte = ft_atoi(argv[3]) * 1000;
	rules->tts = ft_atoi(argv[4]) * 1000;
	rules->forks = ft_calloc(no, sizeof(int));
	rules->mutex = ft_calloc(no, sizeof(pthread_mutex_t));
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	while (no--)
		pthread_mutex_init(&rules->mutex[no], NULL);
	return (rules);
}

t_philo	*p_init(char **argv, t_rules *rules)
{
	int		id;
	t_philo	*philo;
	t_order	*order;

	id = ft_atoi(argv[1]);
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
		philo[id].order = order;
		philo[id].rules = rules;
	}
	return (philo);
}
