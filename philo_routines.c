/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:57:14 by staylan           #+#    #+#             */
/*   Updated: 2025/07/11 18:08:51 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	if (!check_sim_ended(philo->data))
		print_status(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	if (!check_sim_ended(philo->data))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal_time = get_time_ms();
		(philo->meals_eaten)++;
		pthread_mutex_unlock(&philo->meal_lock);
		print_status(philo, "is eating");
		safe_usleep(philo->data->time_to_eat, philo->data);
		pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	}
}

static void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->r_fork]));
		print_status(philo, "has taken a fork");
		if (check_sim_ended(philo->data))
		{
			pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
			return ;
		}
		pthread_mutex_lock(&(philo->data->forks[philo->l_fork]));
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->l_fork]));
		print_status(philo, "has taken a fork");
		if (check_sim_ended(philo->data))
		{
			pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
			return ;
		}
		pthread_mutex_lock(&(philo->data->forks[philo->r_fork]));
		print_status(philo, "has taken a fork");
	}
}

void	handle_fork_taking(t_philo *philo)
{
	if (philo->data->number_of_philos == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[0]));
		print_status(philo, "has taken a fork");
		return ;
	}
	philo_take_forks(philo);
	if (check_sim_ended(philo->data))
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
		return ;
	}
}

void	philo_sleep(t_philo *philo)
{
	if (!check_sim_ended(philo->data))
	{
		print_status(philo, "is sleeping");
		safe_usleep(philo->data->time_to_sleep, philo->data);
	}
}
