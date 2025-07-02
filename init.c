#include "philo.h"

int init_tdata(char **argv, t_data *data, int argc)
{
    int i;

    i = 1;
    while(i < 5)
    {
        if(ft_atoi(argv[i]) <= 0)
            return 0;
        i++;
    }
    data->is_ended = 0;
    data->number_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if(argc == 6 && ft_atoi(argv[5]) >= 0)
        data->number_of_eat = ft_atoi(argv[5]);
    else
        data->number_of_eat = -1;
    if(!init_fork_mutex(data))
        return 0;
    if(pthread_mutex_init(&data->is_ended_lock, NULL) != 0)
        return 0;
    return 1;
}

int init_fork_mutex(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
    if(data->forks == NULL)
        return 0;
    if(pthread_mutex_init(&data->print_lock, NULL) != 0)
    {
        free(data->forks);
        return 0;
    }
    while (i < data->number_of_philos) 
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            pthread_mutex_destroy(&data->print_lock);
            free(data->forks);
            return 0;
        }
        i++;
    }
    return 1;
}

int init_tphilo(t_data *data, t_philo **philo)
{
    int i;

    i = 0;
    *philo = malloc(sizeof(t_philo) * data->number_of_philos);
    if(*philo == NULL)
    {
        destroy_mutex(data, NULL);
        return 0;        
    }
    while(i < data->number_of_philos)
    {
        pthread_mutex_init(&(*philo)[i].meal_lock, NULL);
        (*philo)[i].id = i + 1;
        (*philo)[i].meals_eaten = 0;
        (*philo)[i].last_meal_time = 0;
        (*philo)[i].data = data;
        (*philo)[i].l_fork = i;
        (*philo)[i].r_fork = (i + 1) % data->number_of_philos;
        i++;            
    }
    return 1;
}

void *monitor_philos(void *arg)
{
    int i;
    int eat_flag;
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo[0].data;
    i = 0;
    while(!check_sim_ended(data))
    {
        i = 0;
        while(i < data->number_of_philos)
        {
            pthread_mutex_lock(&philo[i].meal_lock);
            if(get_time_ms() - philo[i].last_meal_time >= data->time_to_die)
            {
                end_condition(data, &philo[i], "died");
                pthread_mutex_unlock(&philo[i].meal_lock);
                return NULL;
            }
            pthread_mutex_unlock(&philo[i].meal_lock);
            i++;
        }
        if(data->number_of_eat > 0)
        {
            i = 0;
            eat_flag = 1;        
            while(i < data->number_of_philos)
            {
                pthread_mutex_lock(&philo[i].meal_lock);
                if(philo[i].meals_eaten < philo[i].data->number_of_eat)
                    eat_flag = 0;
                pthread_mutex_unlock(&philo[i].meal_lock);
                if(!eat_flag)
                    break;
                i++;
            }
            if(eat_flag == 1)
            {
                end_condition(data, &philo[0] ,"All philosophers have eaten enough!");
                return NULL;             
            }            
        }
        usleep(1000);
    }
    return NULL;
}
