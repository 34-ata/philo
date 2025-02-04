/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:55:48 by faata             #+#    #+#             */
/*   Updated: 2024/07/19 14:08:25 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_(t_data *data)
{
	free (data->philosopher);
	free (data->fork);
	pthread_mutex_destroy(&data->eat_mutex);
	exit (EXIT_FAILURE);
}

int	check_status(t_data *data, int i)
{
	while (++i < data->num_of_philo)
	{
		f_check(&data->philosopher[i]);
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philosopher[i].status == DEAD)
		{
			printf("%ld\t%d died\n", time_milisecond(data),
				data->philosopher[i].nmb);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&data->eat_mutex);
	}
	i = -1;
	pthread_mutex_lock(&data->eat_mutex);
	while (data->each_must_eat != -1 && ++i < data->num_of_philo)
		if (data->philosopher[i].eat_count < data->each_must_eat)
			break ;
	if (data->each_must_eat != -1 && i == data->num_of_philo)
		return (EXIT_FAILURE);
	pthread_mutex_unlock(&data->eat_mutex);
	return (EXIT_SUCCESS);
}

int	philo_create(t_data *data, int i)
{
	data->start_time = 0;
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
		data->philosopher[i].l_fork = data->fork + ((i + 1)
				% data->num_of_philo);
		data->philosopher[i].data = data;
		data->philosopher[i].status = ALIVE;
		data->philosopher[i].eat_count = 0;
		data->philosopher[i].last_eat = time_milisecond(data);
		pthread_create(&data->philosopher[i].thread, NULL, func,
			&data->philosopher[i]);
	}
	return (EXIT_SUCCESS);
}

void	p_init(t_data	*data)
{
	if (philo_create(data, -1) == EXIT_FAILURE)
		exit_(data);
	while (1)
		if (check_status(data, -1) == EXIT_FAILURE)
			exit_(data);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("You must give four or five values to program\n"),
			EXIT_FAILURE);
	if (take_args(av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	p_init(&data);
	return (EXIT_SUCCESS);
}
