/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:57:25 by faata             #+#    #+#             */
/*   Updated: 2024/07/17 18:57:26 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define DEAD 1
# define ALIVE 0

typedef struct s_philosopher
{
	int				nmb;
	int				status;
	int				eat_count;
	long			last_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_data	*data;
	pthread_t		thread;
}	t_philosopher;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_must_eat;
	int				eat_count;
	long			start_time;
	struct timeval	time_val;
	pthread_mutex_t	eat_mutex;
	t_philosopher	*philosopher;
	pthread_mutex_t	*fork;
}	t_data;

char	**arg_check(char *av[], int i, int k);
int		ft_check(char *av[], t_data *data, char **nums, int count);
int		numb_of_nums(char **nums);
int		args_to_nums(char **args, t_data *data);
long	time_milisecond(t_data	*data);
void	p_init(t_data *data);
void	free_nums(char **nums);
int		ft_check(char *av[], t_data *data, char **nums, int count);
void	exit_(t_data *data);
void	*func(void	*ph);
void	f_check(t_philosopher *philosopher);

#endif