/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:53:37 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/03 15:14:40 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void free_and_exit(t_table *table)
{
	if (table->philo)
	{
    	pthread_mutex_destroy(&table->philo->mutex);
		free(&table->philo);
	}
	if(table)
	{
    	pthread_mutex_destroy(&table->philo->mutex);
		free(&table->philo);
	}
}

int main(int ac, char **av)
{
	t_table	*table;
    t_philo *table;
    pthread_t *threads;

    if(!wrong_args(ac, av))
    {
        table = (t_table *)malloc(sizeof(t_table));
        if(table)
        {
		    memset(table, 0, sizeof(t_table));
            parser(av, table);
            gettimems();
            threads = create_philo(table, table->philo->n_philo);
        }
        if(!threads || !table)
            printf("end: malloc problem\n");
    }
    free_and_exit(table);
    return (0);
}
