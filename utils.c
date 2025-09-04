/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 21:05:21 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	t_stamp;

	if (gettimeofday(&t_stamp, NULL) != 0)
		return (18446744073709551615UL);
	return (t_stamp.tv_sec * 1000 + t_stamp.tv_usec / 1000);
}

int	ft_usleep(unsigned long duration, t_data *data)
{
	unsigned long	start;
	unsigned long	cur;

	start = get_time();
	if (start == 18446744073709551615UL)
		return (write(2, "Gettimeoftheday failed lol\n", 27), 0);
	while (!check_stop(data))
	{
		cur = get_time();
		if (cur == 18446744073709551615UL)
			return (write(2, "Gettimeoftheday failed lol\n", 27), 0);
		if (cur - start >= duration)
			break ;
		usleep(100);
	}
	return (1);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mut);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mut);
}

void	free_all(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->init_forks)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->log)
		pthread_mutex_destroy(&data->log_mut);
	if (data->phil)
	{
		i = -1;
		while (++i < data->philos)
			pthread_mutex_destroy(&data->phil[i].meal_mut);
		free(data->phil);
		data->phil = NULL;
	}
	if (data->init_run)
		pthread_mutex_destroy(&data->run_mut);
	if (data->init_stop)
		pthread_mutex_destroy(&data->stop_mut);
}

int	wait_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->watcher_count != 0)
		pthread_join(data->watcher, NULL);
	while (++i < data->threads)
		pthread_join(data->phil[i].thread, NULL);
	return (0);
}
