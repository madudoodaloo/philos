/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:40 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/10 22:52:19 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->rdwr);
	if (philo->table->dead < 1)
		printf("%lld %d %s\n", timediff(philo->table->start_time), \
			philo->id, str);
	else if (philo->table->dead == 1 && !strncmp(str, "is dead", strlen(str)))
		printf("%lld %d %s\n", timediff(philo->table->start_time), \
			philo->id, str);
	pthread_mutex_unlock(&philo->table->rdwr);
}

int	wait_now(t_philo *philo, long long time_to)
{
	long long	start;
	long long	status;

	status = 0;
	start = gettimems();
	while (status < time_to && !check_dead(philo))
		status = timediff(start);
	return (0);
}

int	check_dead(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->table->death);
	if ((size_t)timediff(philo->t_last_meal) >= philo->args.t_die)
	{
		philo->table->dead++;
		print(philo, "died");
	}
	flag = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death);
	return (flag);
}
