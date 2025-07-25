#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
	int				phils;
	int				die;
	int				eat;
	int				sleep;
    int             opt_eat_count;
}					t_data;

#endif