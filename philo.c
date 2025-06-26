#include "philo.h"

int create_philos()
{

}


int create_threads()
{

}

void *philo_routines(void *arg)
{
//eat  think sleep
    t_philo *philo;
    philo = (t_philo *)arg;
    while(1)
    {
        philo_think(philo);
        philo_take_forks(philo);
        philo_eat(philo);
        philo_finish_eating(philo);
        philo_sleep(philo);
    }
}

long long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

int	ft_atoi(const char *str)
{
	int         sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
        if(*str == '-')
		    sign *= -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10);
		res = res + (*str - '0');
		str++;
	}
    if((sign == 1 && res > INT_MAX) || (sign == -1 && res < INT_MIN))
        return (-1);
	return (res * sign);
}

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
    data->number_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if(argc == 6 && ft_atoi(argv[5]) >= 0)
        data->number_of_eat = ft_atoi(argv[5]);
    if(!init_fork_mutex(data))
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
        //free
        return 0;        
    }
    while(i < data->number_of_philos)
    {
        philo[i]->id = i + 1;
        philo[i]->meals_eaten = 0;
        philo[i]->last_meal_time = 0;
        philo[i]->data = data;
        philo[i]->l_fork = i;
        philo[i]->r_fork = (i + 1) % data->number_of_philos;
        i++;            
    }
    return 1;
}


int main(int argc, char **argv)
{
    int i;
    t_data data;
    t_philo *philo;
    i = 0;
    if(argc != 6 && argc != 5)
        return 1;
    if(!arg_control(argv))
        return 1;
    if(!init_tdata(argv, &data, argc))
        return 1;
    if(!init_tphilo(&data, &philo))
        return 1;
    data.start_time = get_time_ms();
    while(i < data.number_of_philos)
    {
       pthread_create(&philo[i].thread, NULL, philo_routines, &philo[i]);
       i++;
    }

}