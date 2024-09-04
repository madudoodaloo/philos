/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:44:05 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 13:54:47 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *alive(void *arg)
{
	t_table *table = (t_table *)arg;
	if (table->args->n_philo == 1)
		table_for_one();
	else if ((table->args->n_philo) % 2 == 0)
		table_for_even();
	else
		table_for_odd();
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
    return 0;
}
