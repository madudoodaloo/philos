/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:36:44 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 15:20:29 by msilva-c         ###   ########.fr       */
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

// Expected commandline:
// [n_philos] [t_die] [t_eat] [t_sleep] [n_eat](optional)

typedef struct  s_args
{
    int     n_philo;//av[1] 
    size_t  t_die;  //av[2]
    size_t  t_eat;  //av[3]
    size_t  t_sleep;//av[4]
    size_t     n_eat;  //av[5]
}               t_args;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    size_t          t_last_meal;
    size_t          had_x_meals;
}           t_philo;


typedef struct s_table
{
    t_args          *args;
    int             n_philo;
    int             dead;
    pthread_mutex_t rdwr;
    pthread_mutex_t *forks;
    t_philo         **philo;
    size_t          start_time;
}               t_table;

/* time.c */
unsigned long gettimems(void);

/* threads.c */
void    *alive(void *args);
int set_table(t_table *table, t_philo **philo, char **av);

/* parser.c */
void    parser(char **av, t_philo *args);
size_t  ft_atoi(const char *str);
int     wrong_args(int ac, char **av);

/* testers.c */
void    print_struct(t_philo *args);

/* philo.c */
t_table *init_all(t_table *table, char **av);
int free_and_exit(t_table *table, char *str);


#endif