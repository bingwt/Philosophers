/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:51:27 by btan              #+#    #+#             */
/*   Updated: 2024/04/25 02:50:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(t_error error, char *arg)
{
	printf("philo: ");
	if (error == NOT_ENOUGH_ARGS)
		printf("Not enough arguments: Minimum allowed 4 arguments.\n");
	else if (error == TOO_MANY_ARGS)
		printf("Too many arguments: Maximum allowed is 5 arguments.\n");
	else if (error == NAN)
		printf("Invalid argument: '%s' is not a valid number.\n", arg);
	else if (error == INVALID_INPUT)
		printf("Value too large: '%s' exceeds the maximum integer.\n", arg);
	else if (error == OUT_OF_RANGE)
		printf("Out of Range: Number of Philosophers must be 1 to 200.\n");
	else if (error == MEALS)
		printf("Number of meals must at least be 1.\n");
	return (1);
}

int	invalid_input(char *arg)
{
	char	*ptr;

	ptr = arg;
	while (*ptr)
	{
		if (!(*ptr >= '0' && *ptr <= '9'))
			return (error_msg(NAN, arg));
		ptr++;
	}
	if (ft_atol(arg) > 2147483647)
		return (error_msg(INVALID_INPUT, arg));
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
		return (error_msg(NOT_ENOUGH_ARGS, NULL));
	if (argc > 6)
		return (error_msg(TOO_MANY_ARGS, NULL));
	while (i < argc)
	{
		if (invalid_input(argv[i]))
			return (1);
		i++;
	}
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (error_msg(OUT_OF_RANGE, NULL));
	if (argc == 6 && ft_atol(argv[5]) < 1)
		return (error_msg(MEALS, NULL));
	return (0);
}
