/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by btan              #+#    #+#             */
/*   Updated: 2024/02/05 10:03:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(int no_of_phils, int ttd, int tte, int tts, int must_eat)
{
	printf("Philosophers  : %d\n", no_of_phils);
	printf("Time to die   : %d\n", ttd);
	printf("Time to tte   : %d\n", tte);
	printf("Time to sleep : %d\n", tts);
	printf("Times to eat  : %d\n", must_eat);
}

int	main(int argc, char **argv)
{
	int	no_of_phils;
	int	ttd;
	int	tte;
	int	tts;
	int	must_eat;

	if (argc != 6)
	{
		printf("Please provide 5 arguments!");
		return (1);
	}

	no_of_phils = ft_atoi(argv[1]);
	ttd = ft_atoi(argv[2]);
	tte = ft_atoi(argv[3]);
	tts = ft_atoi(argv[4]);
	must_eat = ft_atoi(argv[5]);

	philosophers(no_of_phils, ttd, tte, tts, must_eat);
	return (0);
}
