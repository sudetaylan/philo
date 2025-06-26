#include "philo.h"

void print_status(t_philo *philo, const char *msg)
{
    long long time;

    pthread_mutex_lock(&(philo->data->print_lock));
    time = get_time_ms() - philo->data->start_time;
    printf("%lld %d %s\n", time, philo->id, msg);
    pthread_mutex_unlock(&(philo->data->print_lock));
}