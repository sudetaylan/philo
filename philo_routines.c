#include "philo.h"

void philo_think(t_philo *philo)
{
    print_status(philo, "is thinking");
}
void philo_eat(t_philo *philo)
{

    philo->last_meal_time = get_time_ms();
    usleep((philo->data->time_to_eat) * 1000);
    (philo->meals_eaten)++;
    print_status(philo, "is eating");
}

void philo_take_forks(t_philo *philo)
{
    int right;
    int left;

    right= philo->r_fork;
    left= philo->l_fork;
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
void philo_drop_forks(t_philo *philo)
{
    int right;
    int left;

    right= philo->r_fork;
    left= philo->l_fork;
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

void philo_sleep(t_philo *philo)
{
    usleep((philo->data->time_to_sleep) * 1000);
    print_status(philo, "is sleeping");

}
