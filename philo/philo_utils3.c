/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:01 by faata             #+#    #+#             */
/*   Updated: 2024/07/17 18:57:37 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_nums(char **nums)
{
	int	i;

	i = -1;
	while (nums[++i])
		free(nums[i]);
	free(nums);
}

int	ft_check(char *av[], t_data *data, char **nums, int count)
{
	nums = arg_check(av, -1, 0);
	if (nums == NULL)
		return (printf("You must give four or five values to program\n"),
			EXIT_FAILURE);
	count = numb_of_nums(nums);
	if (count != 4 && count != 5)
		return (free_nums(nums),
			printf("You must give four or five values to program\n"),
			EXIT_FAILURE);
	if (args_to_nums(nums, data) == EXIT_FAILURE)
		return (free_nums(nums),
			printf("Given values must be in correct range"));
	return (free_nums(nums), EXIT_SUCCESS);
}

void	exit_(t_data *data)
{
	free(data->fork);
	free(data->philosopher);
	exit (EXIT_FAILURE);
}
