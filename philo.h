/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:36:44 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 03:45:11 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_args
{
    int     philos;
    size_t  t_die;
    size_t  t_eat;
    size_t  t_sleep;
    int     x_eat;
}           t_args;

/* threads.c */
int create_philo(t_args *args);


/* parser.c */
void    init_all(t_args *args);
size_t  ft_atoi(const char *str);
void    parser(char **av, t_args *args);
int     wrong_args(int ac, char **av);


/* testers.c */
void    print_struct(t_args *args);



#endif