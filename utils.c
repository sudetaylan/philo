#include "philo.h"

static int is_same(const char *msg, const char *died_msg)
{
    int i;

    i = 0;
    while(msg[i] && died_msg[i])
    {
        if(msg[i] != died_msg[i])
            return 0;
        i++;
    }
    return 1;
}
void print_status(t_philo *philo, const char *msg)
{
    long long time;
    pthread_mutex_lock(&(philo->data->print_lock));
    time = get_time_ms() - philo->data->start_time;
    printf("%lld %d %s\n", time, philo->id, msg);
    pthread_mutex_unlock(&(philo->data->print_lock));
    pthread_mutex_lock(&philo->data->is_ended_lock);
    if (philo->data->is_ended && is_same(msg, "died") == 1)
    {
        pthread_mutex_unlock(&philo->data->is_ended_lock);
        return;
    }
    pthread_mutex_unlock(&philo->data->is_ended_lock);
}

void destroy_mutex(t_data *data, t_philo **philo)
{
    int i;

    i = 0;
    while(i < data->number_of_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;        
    }
    i = 0;
    while(i < data->number_of_philos && (*philo) != NULL)
    {
        pthread_mutex_destroy(&((*philo)[i].meal_lock));
        i++;       
    }
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->is_ended_lock);
    free(data->forks);
}
void   end_condition(t_data *data, t_philo *philo, const char *msg)
{
    pthread_mutex_lock(&philo->data->is_ended_lock);
    data->is_ended = true;
    pthread_mutex_unlock(&philo->data->is_ended_lock);
    print_status(philo, msg);
}

long long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int         sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
        if(*str == '-')
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
    if((sign == 1 && res > INT_MAX) || (sign == -1 && res < INT_MIN))
        return (-1);
	return (res * sign);
}