/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:14 by btan              #+#    #+#             */
/*   Updated: 2024/04/28 04:01:22 by btan             ###   ########.fr       */
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

long	time_ms(long start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld %d %s\n", time_ms(philo->rules->start), philo->no, str);
	pthread_mutex_unlock(&philo->rules->print);
}

void	philo_sleep(long milliseconds)
{
	long	start;

	start = time_ms(0);
	while ((time_ms(0) - start) < milliseconds)
		usleep(500);
}
