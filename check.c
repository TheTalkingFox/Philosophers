/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 19:52:07 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_or_clean(t_data *data)
{
	int	should_cleanup;
	int	should_run;

	while (1)
	{
		pthread_mutex_lock(&data->run_mut);
		should_run = (data->run);
		should_cleanup = (data->cleanup);
		pthread_mutex_unlock(&data->run_mut);
		if (should_run)
			break ;
		if (should_cleanup)
			return (0);
		usleep(100);
	}
	return (1);
}

int	check_stop(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->stop_mut);
	i = data->stop;
	pthread_mutex_unlock(&data->stop_mut);
	return (i);
}

int	check_num(char **arg, int i, int *num)
{
	int	len;

	len = ft_strlength(arg[i]);
	if (len == -1)
		return (0);
	if (is_zero(arg[i]) == len)
		*num = 0;
	else
	{
		*num = ft_atol(arg[i]);
		if (len != count_dig(*num))
			return (write(2, "Incorrect input\n", 16), 0);
	}
	return (1);
}

int	check_arg(int argc, char **argv, t_data *data, int i)
{
	int	num;

	while (++i != argc)
	{
		if (!check_num(argv, i, &num))
			return (0);
		if (num != 0)
		{
			if (i == 1)
				data->philos = num;
			else if (i == 2)
				data->die = num;
			else if (i == 3)
				data->eat = num;
			else if (i == 4)
				data->sleep = num;
			else if (i == 5)
				data->must_eat = num;
		}
		else
			return (write(2, "Should exceed 0\n", 16), 0);
	}
	if (argc != 6)
		data->must_eat = -1;
	return (1);
}
