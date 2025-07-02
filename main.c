#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;

    if(argc != 6 && argc != 5)
        return 1;
    if(!arg_control(argv))
        return 1;
    if(!init_tdata(argv, &data, argc))
        return 1;
    if(!init_tphilo(&data, &philo))
        return 1;
    handle_threads(&data, philo);
    destroy_mutex(&data, philo);
    return 0;
}
