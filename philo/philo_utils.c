/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:14 by btan              #+#    #+#             */
/*   Updated: 2024/04/15 16:44:33 by btan             ###   ########.fr       */
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
