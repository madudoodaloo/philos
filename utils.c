/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:40 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/12 18:43:04 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	check_dead(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->table->death);
	if ((size_t)timediff(philo->t_last_meal) >= philo->args.t_die)
		philo->table->dead += 1;
	flag = philo->table->dead;
	//printf("%d is death\n", flag);
	pthread_mutex_unlock(&philo->table->death);
	return (flag);
}

int	print(int death, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->rdwr);
	death = check_dead(philo);
	// printf("%d is death\n", death);
	if (death == 0 && str)
		printf("%lld %d %s\n", timediff(philo->table->start_time),philo->id, str);
	else if (death == 1 && !philo->table->suicide) {
		printf("%lld %d died\n", timediff(philo->table->start_time),philo->id);
		philo->table->suicide = 1;
	}
	pthread_mutex_unlock(&philo->table->rdwr);
	return (death);
}


