#ifndef PHILO_H
#define PHILO_H

#define INT_MAX 2147483647
#define INT_MIN -2147483648

#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_data{
    int number_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eat;
    int is_ended;// true ise bitti
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
    pthread_mutex_t meal_lock;
    long long last_meal_time;
}t_philo;

void *philo_routines(void *arg);
int arg_control(char **argv);
void print_status(t_philo *philo, const char *msg);
void destroy_mutex(t_data *data, t_philo **philo);
void   end_condition(t_data *data,t_philo *philo, const char *msg);
long long get_time_ms();
int	ft_atoi(const char *str);
int init_tdata(char **argv, t_data *data, int argc);
int init_fork_mutex(t_data *data);
int init_tphilo(t_data *data, t_philo **philo);
void philo_think(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_take_forks(t_philo *philo);
void philo_drop_forks(t_philo *philo);
void philo_sleep(t_philo *philo);
void *monitor_philos(void *arg);
void    safe_usleep(long long duration_ms, t_data *data);
int check_sim_ended(t_data *data);

#endif