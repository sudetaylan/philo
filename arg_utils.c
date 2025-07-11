/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:56:28 by staylan           #+#    #+#             */
/*   Updated: 2025/07/11 18:01:23 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-' && j == 0)
				j++;
			if (argv[i][j] <= '9' && argv[i][j] >= '0')
				;
			else
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10);
		res = res + (*str - '0');
		str++;
	}
	if ((sign == 1 && res > INT_MAX) || (sign == -1 && res < INT_MIN))
		return (-1);
	return (res * sign);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
