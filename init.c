#include "philo.h"

int	init_tdata(char **argv, t_data *data, int argc)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	data->is_ended = 0;
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		data->number_of_eat = ft_atoi(argv[5]);
	else if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (0);
	if (!init_fork_mutex(data))
		return (0);
	if (pthread_mutex_init(&data->is_ended_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (data->forks == NULL)
		return (0);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
	{
		free(data->forks);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->print_lock);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_tphilo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (*philo == NULL)
	{
		destroy_mutex(data, NULL);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&(*philo)[i].meal_lock, NULL);
		(*philo)[i].id = i + 1;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal_time = 0;
		(*philo)[i].data = data;
		(*philo)[i].phi_start_time = get_time_ms();
		(*philo)[i].l_fork = i;
		(*philo)[i].r_fork = (i + 1) % data->number_of_philos;
		i++;
	}
	return (1);
}

void	handle_threads(t_data *data, t_philo *philo)
{
	pthread_t	monitoring;
	int			i;

	i = -1;
	data->start_time = get_time_ms();
	while (++i < data->number_of_philos)
		philo[i].last_meal_time = data->start_time;
	i = -1;
	while (++i < data->number_of_philos)
		pthread_create(&philo[i].thread, NULL, philo_routines, &philo[i]);
	pthread_create(&monitoring, NULL, monitor_philos, philo);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(monitoring, NULL);
}
