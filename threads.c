/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:30:19 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/07 17:25:28 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void    display(t_table *table, t_philo *philo, char *str)
{
    printf("%lld %d %s\n", timediff(table), philo->id, str);
}

void    eat_now(t_table *table, t_philo *philo)
{
    return;
}
void    think_now(t_table *table, t_philo *philo)
{
    table->dead=-1
    return;
}

void    nap_now(t_table *table, t_philo *philo)
{
    return;
} */

void    *alive(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    if (philo->table->n_philo == 1)
        return NULL;
    printf("philo %d has entered routine\n", philo->id );
/*     while (!philo->table->dead)
    {
        eat_now(philo->table, philo);
        sleep_now(philo->table, philo);
        think_now(philo->table, philo);
    } */
   return (NULL);
}

int    simulation(t_table *table, t_philo **philo)
{
    int i;

    table->start_time = gettimems();
    if (table->start_time < 0)
        return(free_and_exit(table, "gettimeof() error"));
    i = -1;
    while (++i < table->n_philo)
    {
        if (pthread_create(&philo[i]->thread, NULL, &alive, philo[i]))
            return(free_and_exit(table, "error creating thread"));
    }
    i = -1;
    while (++i < table->n_philo)
    {
        if (pthread_create(&philo[i]->thread, NULL, &alive, philo[i]))
            return(free_and_exit(table, "error joining thread"));
    }
    return 1;
}
