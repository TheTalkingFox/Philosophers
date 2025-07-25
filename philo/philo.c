#include "philo.h"

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
			return (0);
	}
	return (1);
}

/* int	ft_atoi(const char *c)
{
	int	number;

	number = 0;
	while (*c == 32 || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			(write (2, "Incorrect arg number\n", 21), exit (EXIT_FAILURE));
		c++;
	}
	if (*c < '0' || *c > '9')
		return (0);
	while (*c)
	{
		if (*c >= '0' && *c <= '9')
			number = number * 10 + *c - '0';
		else
			break ;
		c++;
	}
	return (number);
} */

int check_arg(int argc, char **argv, t_data *data)
{
    int i;

    i = 0;
    while (++i < argc)
    {
        is_digit;
        is_int;
        is_pos;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 || argc != 6)
        (write (2, "Incorrect arg number\n", 21), exit (EXIT_FAILURE));
    memset(&data, 0, sizeof(t_data));
    if (!check_arg(argc, argv, data))
        exit (EXIT_FAILURE);
   
    return (0);
}
