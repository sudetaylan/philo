#include "philo.h"

static int	check_philo_died(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (get_time_ms() - philo[i].last_meal_time >= data->time_to_die)
		{
			end_condition(data, &philo[i], "died");
			pthread_mutex_unlock(&philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	return (0);
}

static int	check_all_eaten(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].meals_eaten < philo[i].data->number_of_eat)
		{
			pthread_mutex_unlock(&philo[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	end_condition(data, &philo[0], "All philosophers have eaten enough!");
	return (1);
}

void	*monitor_philos(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo[0].data;
	safe_usleep(data->time_to_eat / 2, data);
	while (!check_sim_ended(data))
	{
		if (check_philo_died(data, philo))
			return (NULL);
		if (data->number_of_eat > 0)
		{
			if (check_all_eaten(data, philo))
				return (NULL);
		}
	}
	return (NULL);
}

void	*philo_routines(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_last_meal_time(philo);
	while (!check_sim_ended(philo->data))
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
