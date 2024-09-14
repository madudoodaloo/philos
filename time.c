/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:20 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/14 18:30:43 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void unsync(long long time_to)
{
	long long start;

	start = gettimems();
	while (gettimems() - start < time_to)
		usleep(50);
	return ;
}

int ft_usleep(t_philo *philo, long long time_to)
{
	long long start;

	start = gettimems();
	while (gettimems() - start < time_to)
	{
		if (check_dead(philo))
			return (print(1, philo, NULL));
		usleep(25);
	}
	return (0);
}

long long	timediff(long long start)
{
	long long	current;

	current = gettimems();
	return (current - start);
}

long long	gettimems(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
