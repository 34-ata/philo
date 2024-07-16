#include "philo.h"

int	main(int ac, char *av[])
{
	t_data	data;

	(void)ac;
	if (ft_check(av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	p_init(&data);
	return (EXIT_SUCCESS);
}
