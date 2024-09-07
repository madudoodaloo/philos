/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:36:44 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/07 17:22:33 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct s_table;
// Expected commandline:
// [n_philos] [t_die] [t_eat] [t_sleep] [n_eat](optional)

typedef struct  s_args
{
    int     n_philo;//av[1] 
    size_t  t_die;  //av[2]
    size_t  t_eat;  //av[3]
    size_t  t_sleep;//av[4]
    int     n_eat;  //av[5]
}               t_args;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    size_t          t_last_meal;
    size_t          had_x_meals;
    struct s_table         *table;
}           t_philo;


typedef struct s_table
{
    t_args          *args;
    int             n_philo;
    int             dead;
    pthread_mutex_t rdwr;
    pthread_mutex_t *forks;
    t_philo         **philo;
    long long       start_time;
}               t_table;

/* time.c */
long long timediff(t_table *table);
long long gettimems(void);

/* threads.c */
int    simulation(t_table *table, t_philo **philo);
void    *alive(void *args);

/* parser.c */
size_t  ft_atoi(const char *str);
int ft_skipspace(int ac, char **av);
int     wrong_args(int ac, char **av);

/* init.c */
int init_all(t_table *table, char **av);
int init_args(t_table *table, char **av);
int init_forks(t_table *table);
int init_philo(t_table *table);
int free_and_exit(t_table *table, char *str);


#endif