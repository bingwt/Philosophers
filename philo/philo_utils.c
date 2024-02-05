/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:51:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/05 11:30:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	value;
	int	neg;

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	char	*ptr;

	arr = malloc(nmemb * size);
	if (arr)
	{
		ptr = (char *) arr;
		while (size > 0)
			ptr[(size--) - 1] = '\0';
	}
	return (arr);
}

void	state_change(int phil, int state)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	if (state == 0)
		printf("%ld %d is sleeping\n", timestamp.tv_usec, phil);
	if (state == 1)
		printf("%ld %d has taken a fork\n", timestamp.tv_usec, phil);
	if (state == 2)
		printf("%ld %d is eating\n", timestamp.tv_usec, phil);
	if (state == 3)
		printf("%ld %d is thinking\n", timestamp.tv_usec, phil);
	if (state == 4)
		printf("%ld %d died\n", timestamp.tv_usec, phil);
}

void	check_philo(t_philo *philo)
{
	if (philo->state == 0)
		printf("%d is sleeping\n", philo->pos);
	if (philo->state == 1)
		printf("%d has taken a fork\n", philo->pos);
	if (philo->state == 2)
		printf("%d is eating\n", philo->pos);
	if (philo->state == 3)
		printf("%d is thinking\n", philo->pos);
	if (philo->state == 4)
		printf("%d is dead\n", philo->pos);
}

void	test(t_pp *pp)
{
	printf("Philosophers  	 : %d\n", pp->phils);
	printf("Time to die   	 : %d\n", pp->ttd);
	printf("Time to eat   	 : %d\n", pp->tte);
	printf("Time to sleep 	 : %d\n", pp->tts);
	printf("Times to eat  	 : %d\n", pp->must_eat);
	printf("Available forks  : %d\n", pp->forks);
	state_change(1, 4);
}
