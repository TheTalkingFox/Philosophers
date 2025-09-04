/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/08/01 21:17:32 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_phil
{
	int				id;
	int				count_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	t_data			*data;
	unsigned long	eat_last;
	pthread_mutex_t	meal_mut;
}					t_phil;

typedef struct s_data
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	int				init_forks;
	pthread_mutex_t	log_mut;
	int				log;
	t_phil			*phil;
	unsigned long	start;
	int				threads;
	int				stop;
	pthread_mutex_t	stop_mut;
	int				init_stop;
	pthread_t		watcher;
	int				watcher_count;
	int				run;
	pthread_mutex_t	run_mut;
	int				init_run;
	int				cleanup;
}					t_data;

int					ft_atol(char *c);
int					ft_strlength(char *str);
int					count_dig(int num);
int					is_zero(char *str);
void				*ft_calloc(size_t nmemb, size_t size);
int					check_num(char **arg, int i, int *num);
int					check_arg(int argc, char **argv, t_data *data, int i);
int					create_forks(t_data *data);
int					create_phils(t_data *data);
int					create_threads(t_data *data);
void				*logic_odd(void *arg);
void				*logic_even(void *arg);
int					run_or_clean(t_data *data);
int					print_log(t_phil *phil, char *action);
int					wait_threads(t_data *data);
void				free_all(t_data *data);
unsigned long		get_time(void);
void				set_stop(t_data *data);
int					check_stop(t_data *data);
void				*watcher_logic(void *arg);
int					ft_usleep(unsigned long duration, t_data *data);
int					is_one(t_phil *phil);

#endif