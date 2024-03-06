/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:49:25 by btan              #+#    #+#             */
/*   Updated: 2024/03/06 20:01:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(int argc)
{
	if (argc < 5)
		printf("Please provide at least %d more argument(s)!!\n\n", 5 - argc);
	if (argc > 6)
		printf("Please provide at least %d less argument(s)!!\n\n", argc - 6);
	printf("Usage: ./philo [options]\n");
	printf("\t[no. of philos]\n");
	printf("\t[time to die]\n");
	printf("\t[time to eat]\n");
	printf("\t[time to sleep]\n");
	printf("\t[times each philo must eat] --optional\n");
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

long	time_ms(time_t start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}
