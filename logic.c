/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 21:29:25 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_f(t_phil *phil, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (check_stop(phil->data))
		return (pthread_mutex_unlock(first_fork), 0);
	if (!print_log(phil, "has taken a fork"))
		return (pthread_mutex_unlock(first_fork), 0);
	pthread_mutex_lock(second_fork);
	if (check_stop(phil->data))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	if (!print_log(phil, "has taken a fork"))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	return (1);
}

int	eat(t_phil *phil, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (!take_f(phil, first_fork, second_fork))
		return (0);
	pthread_mutex_lock(&phil->meal_mut);
	phil->eat_last = get_time();
	if (phil->eat_last == 18446744073709551615UL)
		return (write(2, "Gettimeoftheday failed lol\n", 27),
			pthread_mutex_unlock(&phil->meal_mut),
			pthread_mutex_unlock(second_fork), pthread_mutex_unlock(first_fork),
			0);
	phil->count_eat++;
	pthread_mutex_unlock(&phil->meal_mut);
	if (!print_log(phil, "is eating"))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	if (!ft_usleep(phil->data->eat, phil->data))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	return (1);
}

static int	do_logic(t_phil *phil)
{
	if (phil->id == phil->data->philos)
	{
		if (!eat(phil, phil->right, phil->left))
			return (0);
	}
	else if (!eat(phil, phil->left, phil->right))
		return (0);
	if (phil->data->must_eat > 0 && phil->count_eat >= phil->data->must_eat)
		return (-1);
	print_log(phil, "is sleeping");
	if (!ft_usleep(phil->data->sleep, phil->data))
		return (0);
	print_log(phil, "is thinking");
	return (1);
}

void	*logic_odd(void *arg)
{
	t_phil	*phil;
	int		res;

	phil = (t_phil *)arg;
	if (!run_or_clean(phil->data))
		return (NULL);
	if (!is_one(phil))
		return (NULL);
	if (phil->id % 2 == 0 && phil->id != phil->data->philos)
		usleep(phil->data->eat * 1000);
	else if (phil->id == phil->data->philos)
		usleep(phil->data->eat * 2000);
	while (!check_stop(phil->data))
	{
		res = do_logic(phil);
		if (res == 0)
			return (NULL);
		else if (res == -1)
			break ;
		if (phil->data->sleep < phil->data->eat * 2)
			if (!ft_usleep((phil->data->eat * 2 - phil->data->sleep),
					phil->data))
				return (NULL);
	}
	return (NULL);
}

void	*logic_even(void *arg)
{
	t_phil	*phil;
	int		res;

	phil = (t_phil *)arg;
	if (!run_or_clean(phil->data))
		return (NULL);
	if (phil->id % 2 == 0)
		usleep(phil->data->eat * 1000);
	while (!check_stop(phil->data))
	{
		res = do_logic(phil);
		if (res == 0)
			return (NULL);
		else if (res == -1)
			break ;
		if (phil->data->sleep < phil->data->eat)
			if (!ft_usleep((phil->data->eat - phil->data->sleep), phil->data))
				return (NULL);
	}
	return (NULL);
}
