/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:51:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/20 13:49:44 by btan             ###   ########.fr       */
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

time_t	timestamp_in_ms(time_t start)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000)) - start);
}

int	check_phils(t_philo *phils)
{
	int	i;

	i = 0;
	while (i < phils->total)
	{
		if (phils[i].status == (t_status) DEAD)
		{
			printf("%ld %d died\n", phils->death, phils->num);
			return (0);
		}
		else if (phils[i].must_eat)
			return (1);
		i++;
	}
	printf("All philosophers have eaten\n");
	return (0);
}
