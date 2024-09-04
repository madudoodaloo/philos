/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:36:44 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 12:14:51 by msilva-c         ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct s_philo
{
    int         id;
    pthread_t   thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int     n_philo;//av[1]
    size_t  t_die;  //av[2]
    size_t  t_eat;  //av[3]
    size_t  t_sleep;//av[4]
    int     n_eat;  //av[5]
    int     *alive;
    size_t  last_meal;
}           t_philo;


struct s_table
{
    int             n_philo;
    int             alive;
    pthread_mutex_t rdwr;
    pthread_mutex_t *forks;
    t_philo *philo;
};


/* threads.c */
unsigned long gettimems(void);
void    *alive(void *args);
pthread_t *create_philo(t_philo *args, int n_philo);

/* parser.c */
void init_all(t_philo *args);
size_t  ft_atoi(const char *str);
void    parser(char **av, t_philo *args);
int     wrong_args(int ac, char **av);

/* testers.c */
void    print_struct(t_philo *args);



#endif