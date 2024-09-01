/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:44:05 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 05:23:13 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int food = 0;
pthread_mutex_t mutex;

void    *alive(t_args *args)
{
    while (food <= args->t_eat)
    {
        pthread_mutex_lock(&mutex);
        food++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int create_philo(t_args *args)
{
    pthread_t p1, p2;
    
    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&p1, NULL, &alive, args))
        return (printf("failed to create thread\n"));
    pthread_create(&p2, NULL, &alive, args);
    pthread_join(p1, NULL);
    printf("food total is %d\n", food);
    pthread_join(p2, NULL);
    printf("food total is %d\n", food);
    pthread_mutex_destroy(&mutex);
    printf("food total is %d\n", food);
    return 0;
}