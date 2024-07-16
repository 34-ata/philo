#include "philo.h"

int	f_check(t_philosopher *philosopher)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	if (((time_milisecond(philosopher->data) - philosopher->last_eat))
		> philosopher->data->time_to_die)
			philosopher->status = DEAD;
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
	while (++i < philosopher->data->num_of_philo)
	{
		if (philosopher->data->philosopher[i].status == DEAD)
				return (EXIT_FAILURE);
		printf("STATUS = %d\n", philosopher->status);
	}
	return (EXIT_SUCCESS);
}

void	ft_sleep(t_philosopher *p, long time)
{
	long	dest_time;

	dest_time = time_milisecond(p->data) + time;
	while (time_milisecond(p->data) < dest_time)
		usleep(100);
}

void	*func(void	*ph)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher	*)ph;
	if (philosopher->nmb % 2 == 0)
		usleep(50);
	while (1)
	{
		if (f_check(philosopher) == EXIT_FAILURE)
		{
			printf("%d has died.\n", philosopher->nmb); //sıkıntılı!!!
			break ;
		}
		pthread_mutex_lock(philosopher->r_fork);
		printf("%ld: %d has taken fork.\n", time_milisecond(philosopher->data), philosopher->nmb);
		pthread_mutex_lock(philosopher->l_fork);
		printf("%ld: %d eating.\n", time_milisecond(philosopher->data), philosopher->nmb);
		ft_sleep(philosopher, philosopher->data->time_to_eat);
		philosopher->eat_count++;
		philosopher->last_eat = time_milisecond(philosopher->data);
		pthread_mutex_unlock(philosopher->l_fork);
		pthread_mutex_unlock(philosopher->r_fork);
		printf("%ld: %d has taken a nap.\n", time_milisecond(philosopher->data), philosopher->nmb);
		ft_sleep(philosopher, philosopher->data->time_to_sleep);
	}
	return (NULL);
}

int	p_init(t_data	*data)
{
	int	i;

	i = -1;
	data->start_time = time_milisecond(data);
	data->philosopher = malloc(sizeof(t_philosopher) * data->num_of_philo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (EXIT_FAILURE);
	pthread_mutex_init(&data->eat_mutex, NULL);
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philosopher[i].nmb = i + 1;
		data->philosopher[i].r_fork = data->fork + i;
		data->philosopher[i].l_fork = data->fork + ((i + 1) % data->num_of_philo);
		data->philosopher[i].data = data;
		data->philosopher[i].status = ALIVE;
		data->philosopher[i].eat_count = 0;
		data->philosopher[i].last_eat = time_milisecond(data);
		pthread_create(&data->philosopher[i].thread, NULL, func, &data->philosopher[i]);
	}
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philosopher[i].thread, NULL);
	return (EXIT_SUCCESS);
}