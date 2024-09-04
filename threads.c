/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:44:05 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 13:43:44 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *alive(void *arg)
{
	t_table *args = (t_table *)arg;

    while (food <= 20)
    {
        pthread_mutex_lock(&args->mutex);
        pthread_mutex_unlock(&args->mutex);
    }
    return NULL;
}

int set_table(t_table *table, t_philo **philo, char **av)
{
    int         i;

	i = -1;
    pthread_mutex_init(&table->rdwr, NULL);
    while (++i < table->n_philo)
    {
		philo[i]->id = i + 1;
		philo[i]->left_fork = &table->forks[i];
		if (table->n_philo == 1)
        	philo[i]->right_fork = NULL;
		else
        	philo[i]->right_fork = &table->forks[(i + 1) % table->n_philo];
        if(pthread_create(&philo[i]->thread, NULL, &alive, table))
            return (free_and_exit(table, "failed to create thread"));
    }
	i = -1;
	while (++i < table->n_philo)
	{
		if(pthread_join(philo[i]->thread, NULL) != 0)
            return (free_and_exit(table, "failed to join thread"));
    }
    return table;
}
