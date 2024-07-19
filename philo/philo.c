/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:55:37 by faata             #+#    #+#             */
/*   Updated: 2024/07/19 14:32:19 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_(t_philosopher *philosopher, char	*msg)
{
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	printf("%ld\t%d %s\n", time_milisecond(philosopher->data),
		philosopher->nmb, msg);
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
}

void	f_check(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->eat_mutex);
	if (((time_milisecond(philosopher->data) - philosopher->last_eat))
		> philosopher->data->time_to_die)
		philosopher->status = DEAD;
	pthread_mutex_unlock(&philosopher->data->eat_mutex);
}

void	ft_sleep(t_philosopher *p, long time)
{
	long	dest_time;

	dest_time = time_milisecond(p->data) + time;
	while (time_milisecond(p->data) < dest_time)
		usleep(500);
}

void	life_cycle(t_philosopher *philosopher)
{
	while (1)
	{
		pthread_mutex_lock(philosopher->r_fork);
		print_(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->l_fork);
		print_(philosopher, "has taken a fork");
		print_(philosopher, "is eating");
		pthread_mutex_lock(&philosopher->data->eat_mutex);
		philosopher->eat_count++;
		philosopher->last_eat = time_milisecond(philosopher->data);
		pthread_mutex_unlock(&philosopher->data->eat_mutex);
		ft_sleep(philosopher, philosopher->data->time_to_eat);
		pthread_mutex_unlock(philosopher->l_fork);
		pthread_mutex_unlock(philosopher->r_fork);
		print_(philosopher, "is sleeping");
		ft_sleep(philosopher, philosopher->data->time_to_sleep);
		print_(philosopher, "is thinking");
	}
}

void	*func(void	*ph)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ph;
	if (philosopher->data->num_of_philo == 1)
	{
		ft_sleep(philosopher, philosopher->data->time_to_die);
		f_check(philosopher);
		usleep(2000);
	}
	if (philosopher->nmb % 2 == 0)
		usleep(750);
	life_cycle(philosopher);
	return (NULL);
}
