/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 21:25:26 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_log(t_phil *phil, char *action)
{
	unsigned long	t_stamp;
	unsigned long	cur;

	pthread_mutex_lock(&phil->data->log_mut);
	if (!check_stop(phil->data))
	{
		cur = get_time();
		if (cur == 18446744073709551615UL)
			return (write(2, "Gettimeoftheday failed lol\n", 27),
				pthread_mutex_unlock(&phil->data->log_mut), 0);
		t_stamp = cur - phil->data->start;
		printf("%lu %d %s\n", t_stamp, phil->id, action);
	}
	return (pthread_mutex_unlock(&phil->data->log_mut), 1);
}

int	is_one(t_phil *phil)
{
	if (phil->data->philos == 1)
	{
		pthread_mutex_lock(phil->left);
		if (!print_log(phil, "has taken a fork"))
			return (pthread_mutex_unlock(phil->left), 0);
		usleep(phil->data->die * 1000 + 1000);
		pthread_mutex_unlock(phil->left);
		return (0);
	}
	return (1);
}

int	check_dead(t_data *data, unsigned long t_stamp, int *eat_count)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		pthread_mutex_lock(&data->phil[i].meal_mut);
		if (t_stamp - data->phil[i].eat_last > (unsigned long)data->die)
		{
			set_stop(data);
			pthread_mutex_unlock(&data->phil[i].meal_mut);
			pthread_mutex_lock(&data->log_mut);
			printf("%lu %d died\n", t_stamp - data->start, data->phil[i].id);
			pthread_mutex_unlock(&data->log_mut);
			return (0);
		}
		if (data->must_eat > 0 && data->phil[i].count_eat < data->must_eat)
			*eat_count = 0;
		pthread_mutex_unlock(&data->phil[i].meal_mut);
	}
	return (1);
}

void	*watcher_logic(void *arg)
{
	t_data			*data;
	unsigned long	t_stamp;
	int				eat_count;

	data = (t_data *)arg;
	if (!run_or_clean(data))
		return (NULL);
	while (!check_stop(data))
	{
		eat_count = 1;
		t_stamp = get_time();
		if (t_stamp == 18446744073709551615UL)
			return (write(2, "Gettimeoftheday failed lol\n", 27), NULL);
		if (!check_dead(data, t_stamp, &eat_count))
			return (NULL);
		if (data->must_eat > 0 && eat_count)
			return (set_stop(data), NULL);
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (write(2, "Incorrect arg amount\n", 21), 1);
	memset(&data, 0, sizeof(t_data));
	if (!check_arg(argc, argv, &data, 0))
		return (1);
	if (!create_forks(&data))
		return (free(data.forks), 1);
	if (!create_phils(&data))
		return (free(data.forks), 1);
	if (pthread_mutex_init(&data.log_mut, NULL))
		return (free_all(&data), write(2, "Init log mutex failed\n", 22), 1);
	else
		data.log = 1;
	if (pthread_mutex_init(&data.stop_mut, NULL))
		return (free_all(&data), write(2, "Init stop mutex failed\n", 23), 1);
	else
		data.init_stop = 1;
	data.start = get_time();
	if (data.start == 18446744073709551615UL)
		return (write(2, "Gettimeoftheday failed lol\n", 27), 1);
	if (!create_threads(&data))
		return (wait_threads(&data), free_all(&data), 1);
	return (wait_threads(&data), free_all(&data), 0);
}
