/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:19 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 18:40:36 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *alive(void *args)
{
    t_table *table;

    table = (t_table *)args;
}

int    simulation(t_table *table, t_philo **philo, t_args *args)
{
    int i;

    table->start_time = gettimems();
    if (table->start_time < 0)
        return(free_and_exit(table, "gettimeof() error"));
    i = -1;
    while (++i < table->n_philo)
    {
        if (pthread_create(&philo[i]->thread, NULL, &alive, table))
            return(free_and_exit(table, "error creating thread"));
    }
    i = -1;
    while (++i < table->n_philo)
    {
        if (pthread_create(&philo[i]->thread, NULL, &alive, table))
            return(free_and_exit(table, "error joining thread"));
    }
    
}
