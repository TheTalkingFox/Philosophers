/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:36:24 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/26 03:25:38 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(char *c)
{
	long long	number;

	number = 0;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			return (write (2, "Negative number\n", 16), 0);
		c++;
	}
	if (*c == 0)
		while (*c == 0)
			c++;
	while (*c >= '0' && *c <= '9')
	{
		number = number * 10 + *c - '0';
		c++;
	}
	if (number > 2147483647)
		return (write (2, "INT MAX exceeded\n", 17), 0);
	return (number);
}

int	ft_strlength(char *str)
{
	int	len;

	len = 0;
	if (*str == '-')
		return (write (2, "Negative number\n", 16), -1);
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (write (2, "Empty input\n", 12), -1);
	while (*str == '0')
		str++;
	while (*str)
	{
		str++;
		len++;
	}
	if (len == 0)
		return (1);
	return (len);
}

int	count_dig(int num)
{
	int	len;

	len = 0;
	if (num == -2147483648)
		return (10);
	else if (num < 0)
		num *= -1;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	is_zero(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	full_size;
	void	*p;
	char	*byte_p;
	size_t	i;

	full_size = nmemb * size;
	if (size == 0 || (nmemb != 0 && full_size / nmemb != size))
		return (malloc(0));
	p = malloc(full_size);
	if (p == 0)
		return (0);
	byte_p = (char *)p;
	i = 0;
	while (i < full_size)
	{
		byte_p[i] = 0;
		i++;
	}
	return (p);
}
