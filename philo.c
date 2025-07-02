#include "philo.h"

void *philo_routines(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 != 0)
        safe_usleep(1, philo->data);
    while(!check_sim_ended(philo->data))
    {
        philo_take_forks(philo);
        philo_eat(philo);
        philo_drop_forks(philo);
        if(check_sim_ended(philo->data))
            break;
        philo_sleep(philo);
        philo_think(philo);    
    }
    return NULL;
}

int arg_control(char **argv)
{
    int i;
    int j;

    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if(argv[i][j] == '-' && j == 0)
                j++;
            if(argv[i][j] <= '9' && argv[i][j] >= '0')
                ;
            else
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int i;
    t_data data;
    t_philo *philo;
    pthread_t monitoring;

    i = 0;
    if(argc != 6 && argc != 5)
        return 1;
    if(!arg_control(argv))
        return 1;
    if(!init_tdata(argv, &data, argc))
        return 1;
    if(!init_tphilo(&data, &philo))
        return 1;
    while(i < data.number_of_philos)
    {
        data.start_time = get_time_ms();
        philo[i].last_meal_time = data.start_time;
        pthread_create(&philo[i].thread, NULL, philo_routines, &philo[i]);
        i++;
    }
    pthread_create(&monitoring, NULL, monitor_philos, philo);
    i = 0;
    while(i < data.number_of_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(monitoring, NULL);
    destroy_mutex(&data, &philo);
    free(philo);
    return 0;
}
