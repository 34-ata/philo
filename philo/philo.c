#include "philo.h"

void f_check(t_philosopher *philosopher)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philosopher->data->status_mutex);
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	if (((time_milisecond(philosopher->data) - philosopher->last_eat))
		> philosopher->data->time_to_die)
			philosopher->status = DEAD;
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
	pthread_mutex_unlock(&philosopher->data->status_mutex);
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
		f_check(philosopher);
		pthread_mutex_lock(philosopher->r_fork);
		pthread_mutex_lock(&philosopher->data->print_mutex);
		printf("[%lld]: %d has taken fork.\n", time_milisecond(philosopher->data), philosopher->nmb);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		pthread_mutex_lock(philosopher->l_fork);
		pthread_mutex_lock(&philosopher->data->print_mutex);
		printf("[%lld]: %d eating.\n", time_milisecond(philosopher->data), philosopher->nmb);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		ft_sleep(philosopher, philosopher->data->time_to_eat);
		f_check(philosopher);
		philosopher->eat_count++;
		philosopher->last_eat = time_milisecond(philosopher->data);
		f_check(philosopher);
		pthread_mutex_unlock(philosopher->l_fork);
		pthread_mutex_unlock(philosopher->r_fork);
		pthread_mutex_lock(&philosopher->data->print_mutex);
		printf("[%lld]: %d has taken a nap.\n", time_milisecond(philosopher->data), philosopher->nmb);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		f_check(philosopher);
		ft_sleep(philosopher, philosopher->data->time_to_sleep);
		f_check(philosopher);
	}
	return (NULL);
}

int	p_init(t_data	*data)
{
	int	i;

	i = -1;
	data->start_time = 0;
	data->start_time = time_milisecond(data);
	data->philosopher = malloc(sizeof(t_philosopher) * data->num_of_philo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (EXIT_FAILURE);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->status_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
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
	while (1)
	{
		i = -1;
		while (++i < data->num_of_philo)
		{
			pthread_mutex_lock(&data->status_mutex);
			if (data->philosopher[i].status == DEAD)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("[%lld] %d has died.\n", time_milisecond(data), data->philosopher[i].nmb);
				exit (1);
			}
			pthread_mutex_unlock(&data->status_mutex);
		}
	}
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philosopher[i].thread, NULL);
	return (EXIT_SUCCESS);
}