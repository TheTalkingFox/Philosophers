/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 21:05:42 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread_func(t_data *data, int i, int mod)
{
	if (mod == 0)
	{
		if (data->philos % 2 == 1)
		{
			if (pthread_create(&data->phil[i].thread, NULL, logic_odd,
					&data->phil[i]))
				return (0);
		}
		else if (data->philos % 2 == 0)
		{
			if (pthread_create(&data->phil[i].thread, NULL, logic_even,
					&data->phil[i]))
				return (0);
		}
	}
	else
	{
		if (pthread_create(&data->watcher, NULL, watcher_logic, data))
		{
			pthread_mutex_lock(&data->run_mut);
			data->cleanup = 1;
			return (pthread_mutex_unlock(&data->run_mut), 0);
		}
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->run_mut, NULL))
		return (write(2, "Init run mutex failed\n", 22), 0);
	else
		data->init_run = 1;
	while (++i < data->philos)
	{
		if (!create_thread_func(data, i, 0))
		{
			pthread_mutex_lock(&data->run_mut);
			data->cleanup = 1;
			pthread_mutex_unlock(&data->run_mut);
			return (write(2, "Philo thread failed\n", 20), 0);
		}
		data->threads++;
	}
	if (!create_thread_func(data, 0, 1))
		return (write(2, "Watcher thread failed\n", 22), 0);
	else
		data->watcher_count++;
	pthread_mutex_lock(&data->run_mut);
	data->run = 1;
	return (pthread_mutex_unlock(&data->run_mut), 1);
}

int	create_forks(t_data *data)
{
	int	i;

	data->forks = ft_calloc(data->philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (write(2, "Memory alloc failed\n", 20), 0);
	i = -1;
	while (++i < data->philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write(2, "Init forks mutex failed\n", 24), 0);
		data->init_forks++;
	}
	return (1);
}

int	create_phils(t_data *data)
{
	int				i;
	unsigned long	t_stamp;

	data->phil = ft_calloc(data->philos, sizeof(t_phil));
	if (!data->phil)
		return (write(2, "Memory alloc failed\n", 20), 0);
	i = -1;
	t_stamp = get_time();
	if (t_stamp == 18446744073709551615UL)
		return (write(2, "Gettimeoftheday failed lol\n", 27), 0);
	while (++i < data->philos)
	{
		data->phil[i].id = i + 1;
		data->phil[i].data = data;
		data->phil[i].count_eat = 0;
		data->phil[i].left = &data->forks[i];
		data->phil[i].right = &data->forks[(i + 1) % data->philos];
		data->phil[i].eat_last = t_stamp;
		if (pthread_mutex_init(&data->phil[i].meal_mut, NULL))
			return (write(2, "Init meal mutex failed\n", 23), 0);
	}
	return (1);
}
