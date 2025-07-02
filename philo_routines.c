#include "philo.h"

void philo_think(t_philo *philo)
{
    if(!check_sim_ended(philo->data))
        print_status(philo, "is thinking");
}
void philo_eat(t_philo *philo)
{
    if(!check_sim_ended(philo->data))
    {
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal_time = get_time_ms();
        (philo->meals_eaten)++;
        pthread_mutex_unlock(&philo->meal_lock);
        print_status(philo, "is eating");
        safe_usleep(philo->data->time_to_eat, philo->data);
    }
}

void philo_take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->id % 2 == 0)
    {
        first_fork = &philo->data->forks[philo->r_fork];
        second_fork = &philo->data->forks[philo->l_fork];
    }
    else 
    {
        first_fork = &philo->data->forks[philo->l_fork];
        second_fork = &philo->data->forks[philo->r_fork];
    }
    pthread_mutex_lock(first_fork);
    print_status(philo, "has taken a fork");
    if (check_sim_ended(philo->data))
    {
        pthread_mutex_unlock(first_fork);
        return;
    }
    pthread_mutex_lock(second_fork);
    print_status(philo, "has taken a fork");
}

void philo_drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
    print_status(philo, "has dropped a fork");
    pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
    print_status(philo, "has dropped a fork");
}

void philo_sleep(t_philo *philo)
{   
    if(!check_sim_ended(philo->data))
    {
        print_status(philo, "is sleeping");
        safe_usleep(philo->data->time_to_sleep, philo->data);
    }
}
