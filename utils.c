#include "philo.h"

void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	philo->phi_start_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
}

int	check_sim_ended(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->is_ended_lock);
	status = data->is_ended;
	pthread_mutex_unlock(&data->is_ended_lock);
	return (status);
}

void	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&(philo->data->print_lock));
	if (!check_sim_ended(philo->data))
		printf("%lld %d %s\n", get_time_ms() - philo->phi_start_time,
			philo->id, msg);
	pthread_mutex_unlock(&(philo->data->print_lock));
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_usleep(long long duration_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < duration_ms)
	{
		pthread_mutex_lock(&data->is_ended_lock);
		if (data->is_ended)
		{
			pthread_mutex_unlock(&data->is_ended_lock);
			return ;
		}
		pthread_mutex_unlock(&data->is_ended_lock);
		usleep(50);
	}
}
