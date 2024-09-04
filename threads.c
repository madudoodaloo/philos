/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:44:05 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/03 14:53:26 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long gettimems()
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL) == -1)
		return (printf("couldn't get time\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int food = 0;

void    *alive(void *arg)
{
	t_philo *args = (t_philo *)arg;

    while (food <= 20)
    {
        pthread_mutex_lock(&args->mutex);
        food++;
        pthread_mutex_unlock(&args->mutex);
    }
    return NULL;
}

pthread_t *create_philo(t_philo *args, int n_philo)
{
    pthread_t   *table;
    int         i;

	i = -1;
    table = (pthread_t *)malloc(sizeof(pthread_t) * args->n_philo);
    if (!table)
        return (NULL);
    pthread_mutex_init(&args->mutex, NULL);
    while (++i < n_philo)
    {
        if(pthread_create(&table[i], NULL, &alive, args) != 0)
        {
            printf("failed to create thread %d\n", i);
            return (table);
        }
		printf("%d philo was born\n", i);
    }
	i = -1;
	while (++i < n_philo)
	{
		if(pthread_join(table[i], NULL) != 0)
        {
            printf("failed to join thread %d\n", i);
            return (table);
        }
		printf("%d thread was joined\n", i);
    }
	gettimems();
    pthread_mutex_destroy(&args->mutex);
    return table;
}
