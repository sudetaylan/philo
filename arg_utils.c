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
				return (0);
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
	if (*str == '+')
		str++;
	if (!(*str >= '0' && *str <= '9'))
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
