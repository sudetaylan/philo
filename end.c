/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:56:45 by staylan           #+#    #+#             */
/*   Updated: 2025/07/11 17:56:52 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos && philo != NULL)
	{
		pthread_mutex_destroy(&((philo)[i].meal_lock));
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->is_ended_lock);
	free(data->forks);
	free(philo);
}

void	end_condition(t_data *data, t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->is_ended_lock);
	data->is_ended = 1;
	pthread_mutex_unlock(&philo->data->is_ended_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("%lld %d %s\n",
		get_time_ms() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&(data->print_lock));
}
