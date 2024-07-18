/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:55:57 by faata             #+#    #+#             */
/*   Updated: 2024/07/18 13:13:17 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_milisecond(t_data	*data)
{
	gettimeofday(&data->time_val, NULL);
	return ((data->time_val.tv_usec / 1000
			+ data->time_val.tv_sec * 1000) - data->start_time);
}
