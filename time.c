/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:42:40 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/06 16:41:52 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timediff(t_table *table)
{
    return (table->start_time - gettimems());
}

long long gettimems(void)
{
    struct timeval	tv;

	if(gettimeofday(&tv, NULL))
        return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
