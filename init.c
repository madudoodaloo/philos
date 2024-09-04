/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:18:52 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 18:32:55 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int free_and_exit(t_table *table, char *str)
{
    int i;

    i = -1;
    if (table)
    {
        if (table->args)
            free(table->args);
        if (table->forks)
            free(table->forks);
        if (table->philo)
        {
            while (table->philo[++i])
                free(table->philo[i]);
            free(table->philo);
        }
        free(table);
    }
    if (str)
        return(printf("%s\n", str));
    return (0);
}

int   init_args(t_table *table, char **av)
{
    table->args = (t_args *)malloc(sizeof(t_args));
    if (!table->args)
        return 0;
    table->args->n_philo = ft_atoi(av[1]);
    table->args->t_die = ft_atoi(av[2]);
    table->args->t_eat = ft_atoi(av[3]);
    table->args->t_sleep = ft_atoi(av[4]);
    if (av[5])
        table->args->n_eat = ft_atoi(av[5]);  
    else
        table->args->n_eat = -1;  
    return 1;
}

int    init_forks(t_table *table)
{
    int i;

    i = -1;
    table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->n_philo);
    if (!table->forks)
        return 0;
    while (++i < table->n_philo)
        if (pthread_mutex_init(&table->forks[i], NULL))
            return 0;
    return 1;
}

int init_philo(t_table *table)
{
    int i;
    i = -1;
    table->philo = (t_philo **)malloc(sizeof(t_philo *));
    if (!table->philo)
        return 0;
    while (++i < table->n_philo)
    {
        table->philo[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!table->philo[i])
            return 0;
        memset(table->philo[i], 0, sizeof(t_philo));
        printf("%zu is the last time %d has eaten\n", table->philo[i]->t_last_meal, i + 1);
        table->philo[i]->id = i + 1;
        table->philo[i]->left_fork = &table->forks[i];
        if (table->n_philo == 1)
            table->philo[i]->right_fork = NULL;
        else
            table->philo[i]->right_fork = &table->forks[(i + 1) % table->n_philo];
    }
    return (1);
}


int init_all(t_table *table, char **av)
{
    int ret;

    ret = 0;
    table->n_philo = ft_atoi(av[1]);
    table->dead = 0;
    table->start_time = 0;
    pthread_mutex_init(&table->rdwr, NULL);
    ret = init_args(table, av);
    ret = init_forks(table);
    ret = init_philo(table);
    return (ret);
}
