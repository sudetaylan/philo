#ifndef PHILO_H
#define PHILO_H

#define INT_MAX 2147483647
#define INT_MIN -2147483648

#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_data{
    int number_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eat;
    bool is_ended;// true ise bitti
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t is_ended_lock;
}t_data;

typedef struct s_philo{
    int id;
    int meals_eaten;
    int r_fork;
    int l_fork;
    t_data *data;
    pthread_t thread;
    long long last_meal_time;
}t_philo;


void print_status(t_philo *philo, const char *msg);
long long get_time_ms();
#endif