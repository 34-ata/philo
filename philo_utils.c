#include "philo.h"

int	ft_check(char *av[], t_data *data)
{
	char	**nums;
	int		count;

	nums = arg_check(av, -1, 0);
	if (nums == NULL)
		return (printf("You must give four or five values to program\n"),
			EXIT_FAILURE);
	count = numb_of_nums(nums);
	if (count != 4 && count != 5)
		return (printf("You must give four or five values to program\n"),
			EXIT_FAILURE);
	if (args_to_nums(nums, data) == EXIT_FAILURE)
		return (printf("Given values must be in correct range"));
	return (EXIT_SUCCESS);
}

char	*sub(char *str, int start, int end)
{
	char	*temp;
	int		i;

	temp = malloc(sizeof(char) * (end - start) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (start != end)
		temp[i++] = str[start++];
	temp[i] = '\0';
	return (temp);
}

int	arg_count(char *av[], char *nums, int i, int count)
{
	int		start;
	int		j;

	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			while (av[i][j] && !(av[i][j] >= '0' && av[i][j] <= '9'))
				j++;
			if (!av[i][j])
				break ;
			start = j;
			while (av[i][j] && av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			nums = sub(av[i], start, j);
			if (!nums)
				return (0);
			free(nums);
			count++;
		}
		i++;
	}
	return (count);
}

int	arg_check2(char *av, int *start, int *j)
{
	while (av[*j] && !(av[*j] >= '0' && av[*j] <= '9')
		&& av[*j] != '-' && av[*j] != '+')
		*j += 1;
	if (!av[*j])
		return (EXIT_FAILURE);
	*start = *j;
	while (av[*j] == '-' || av[*j] == '+')
		*j += 1;
	while (av[*j] && av[*j] >= '0' && av[*j] <= '9')
		*j += 1;
	return (EXIT_SUCCESS);
}

char	**arg_check(char *av[], int i, int k)
{
	char	**nums;
	int		start;
	int		j;

	if (arg_count(av, NULL, 1, 0) == 0)
		return (NULL);
	nums = malloc((sizeof(char *) * arg_count(av, NULL, 1, 0)) + 1);
	nums[arg_count(av, NULL, 1, 0)] = NULL;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (arg_check2(av[i], &start, &j) == EXIT_FAILURE)
				break ;
			nums[k] = sub(av[i], start, j);
			if (!nums[k++])
				return (free(nums), NULL);
		}
	}
	return (nums);
}
