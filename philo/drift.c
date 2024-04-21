#include "philo.h"

int	main()
{
	int		ms;
	long	timestamp;

	ms = 500;
	while (1)
	{
		timestamp = time_ms(0);
		printf("%ld\n", timestamp);
		usleep(ms * 1000);
		timestamp = time_ms(timestamp);
		printf("%ld\n", timestamp);
	}
}
