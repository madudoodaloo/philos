/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:35:36 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 14:24:38 by msilva-c         ###   ########.fr       */
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
