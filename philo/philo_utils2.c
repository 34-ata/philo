#include "philo.h"

long long time_milisecond(t_data	*data)
{
	gettimeofday(&data->time_val, NULL);
	return ((long long )((data->time_val.tv_usec / 1000
		+ data->time_val.tv_sec * 1000) - data->start_time));
}

int	numb_of_nums(char **nums)
{
	int	count;

	count = 0;
	while (nums[count])
		count++;
	return (count);
}

void	take_nums(int	*nums, t_data *data, int i)
{
	if (i == 4)
		data->each_must_eat = nums[i--];
	data->time_to_sleep = nums[i--];
	data->time_to_eat = nums[i--];
	data->time_to_die = nums[i--];
	data->num_of_philo = nums[i--];
}

long	args_to_nums2(char *args)
{
	long	temp;
	int		sign;
	int		j;

	sign = 1;
	temp = 0;
	j = 0;
	while (args[j])
	{
		while (args[j] == '-' || args[j] == '+')
		{
			if (args[j] == '-')
				sign *= -1;
			j++;
		}
		while (args[j] && args[j] >= '0' && args[j] <= '9')
		{
			temp *= 10;
			temp += args[j] - 48;
			j++;
		}
	}
	return (temp * sign);
}

int	args_to_nums(char **args, t_data *data)
{
	int		*nums;
	long	temp;
	int		i;

	nums = malloc(sizeof(int *) * numb_of_nums(args));
	i = 0;
	while (args[i])
	{
		temp = args_to_nums2(args[i]);
		if (temp > 2147483647 || temp < 0)
			return (free(nums), EXIT_FAILURE);
		nums[i] = (int)temp;
		i++;
	}
	take_nums(nums, data, --i);
	return (EXIT_SUCCESS);
}
