#include "philo.h"

void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
    philo->phi_start_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
}
void print_status(t_philo *philo, const char *msg)
{
    pthread_mutex_lock(&(philo->data->print_lock));
    if(!check_sim_ended(philo->data))
        printf("%lld %d %s\n", get_time_ms() - philo->phi_start_time, philo->id, msg);
    pthread_mutex_unlock(&(philo->data->print_lock));
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
    int i;

    i = 0;
    pthread_mutex_lock(&philo->data->is_ended_lock);
    data->is_ended = 1;
    pthread_mutex_unlock(&philo->data->is_ended_lock);
    while(i < data->number_of_philos)
    {
        pthread_mutex_unlock(&data->forks[i]);
        i++;
    }
    pthread_mutex_lock(&data->print_lock);
    printf("%lld %d %s\n", get_time_ms() - philo->phi_start_time, philo->id, msg);
    pthread_mutex_unlock(&(data->print_lock));
}

long long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
int check_sim_ended(t_data *data)
{
    pthread_mutex_lock(&data->is_ended_lock);
    int status = data->is_ended;
    pthread_mutex_unlock(&data->is_ended_lock);
    return status;
}
void    safe_usleep(long long duration_ms, t_data *data)
{
    long long start_time;

    start_time = get_time_ms();
    while (get_time_ms() - start_time < duration_ms)
    {
        pthread_mutex_lock(&data->is_ended_lock);
        if (data->is_ended)
        {
            pthread_mutex_unlock(&data->is_ended_lock);
            return;
        }
        pthread_mutex_unlock(&data->is_ended_lock);
        usleep(50);
    }
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