/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:18:52 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 15:29:49 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *init_all(t_table *table, char **av)
{
    table = (t_table *)malloc(sizeof(t_table));
    if(table)
    {
        table->n_philo = ft_atoi(av[1]);
        table->dead = 0;
        table->rdwr = pthread_attr_init
        table->args = (t_args *)malloc(sizeof(t_args));
        if (!table->args)
            return table;
        table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        if (!table->forks)
            return (table);
        table->philo = (t_philo **)malloc(sizeof(t_philo *) * table->n_philo);
        if (table->philo)
            return (table);
    }
}
