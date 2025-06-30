#include "philo.h"

void philo_think(t_philo *philo)
{
    if(!philo->data->is_ended)
        print_status(philo, "is thinking");
}
void philo_eat(t_philo *philo)
{
    if(!philo->data->is_ended)
    {
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal_time = get_time_ms();
        (philo->meals_eaten)++;
        pthread_mutex_unlock(&philo->meal_lock);
        print_status(philo, "is eating");
        usleep((philo->data->time_to_eat) * 1000);        
    }
}

void philo_take_forks(t_philo *philo)
{
    int right;
    int left;

    right= philo->r_fork;
    left= philo->l_fork;
    if(!philo->data->is_ended)
    {
        if(right > left)
        {
            pthread_mutex_lock(&(philo->data->forks[left]));
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(&(philo->data->forks[right]));
            print_status(philo, "has taken a fork");
        }
        else if(left > right)
        {
            pthread_mutex_lock(&(philo->data->forks[right]));
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(&(philo->data->forks[left]));
            print_status(philo, "has taken a fork");
        }
    }
}
void philo_drop_forks(t_philo *philo)
{
    int right;
    int left;

    right= philo->r_fork;
    left= philo->l_fork;
    if(!philo->data->is_ended)
    {
        if(right > left)
        {
            pthread_mutex_unlock(&(philo->data->forks[right]));
            print_status(philo, "has dropped a fork");
            pthread_mutex_unlock(&(philo->data->forks[left]));
            print_status(philo, "has dropped a fork");
        }
        else if(left > right)
        {
            pthread_mutex_unlock(&(philo->data->forks[left]));
            print_status(philo, "has dropped a fork");
            pthread_mutex_unlock(&(philo->data->forks[right]));
            print_status(philo, "has dropped a fork");
        }
    }
}

void philo_sleep(t_philo *philo)
{   
    if(!philo->data->is_ended)
    {
        print_status(philo, "is sleeping");
        usleep((philo->data->time_to_sleep) * 1000);
    }
}
