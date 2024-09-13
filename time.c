/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:20 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/12 18:50:26 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long long time_to)
{
	long long start;

	start = gettimems();
	while (gettimems() - start < time_to)
		usleep(60);
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
