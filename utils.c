/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:57:54 by staylan           #+#    #+#             */
/*   Updated: 2025/07/11 18:01:16 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

long long	get_last_meal_time(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&(philo->meal_lock));
	time = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->meal_lock));
	return (time);
}

void	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&(philo->data->print_lock));
	if (!check_sim_ended(philo->data))
		printf("%lld %d %s\n",
			get_time_ms() - philo->phi_start_time, philo->id, msg);
	pthread_mutex_unlock(&(philo->data->print_lock));
}

void	safe_usleep(long long duration_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < duration_ms)
	{
		if (check_sim_ended(data))
			return ;
		usleep(50);
	}
}
