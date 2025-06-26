#include "philo.h"

int philo_think(t_philo *philo)
{
    
}
int philo_eat(t_philo *philo)
{

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
        pthread_mutex_lock(&(philo->data->forks[right]));

    }
    else if(left > right)
    {
        pthread_mutex_lock(&(philo->data->forks[right]));
        pthread_mutex_lock(&(philo->data->forks[left]));
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
        pthread_mutex_unlock(&(philo->data->forks[left]));
    }
    else if(left > right)
    {
        pthread_mutex_unlock(&(philo->data->forks[left]));
        pthread_mutex_unlock(&(philo->data->forks[right]));
    }
}

int philo_sleep(t_philo *philo)
{


}
