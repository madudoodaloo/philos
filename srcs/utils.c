/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:40 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/14 19:22:09 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	countmeal(t_philo *philo, int flag)
{
	int	i;

	pthread_mutex_lock(&philo->table->meal_counter);
	if (flag)
		philo->table->total_meals++;
	i = philo->table->total_meals;
	pthread_mutex_unlock(&philo->table->meal_counter);
	return (i);
}

int	check_dead(t_philo *philo)
{
	int			flag;
	long long	diff;

	pthread_mutex_lock(&philo->table->death);
	diff = gettimems() - philo->t_last_meal;
	if (diff >= (long long)philo->args.t_die)
		philo->table->dead += 1;
	flag = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death);
	return (flag);
}

int	print(int death, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->rdwr);
	death = check_dead(philo);
	if (death == 0 && str)
	{
		printf("%lld %d %s\n", (long long)timediff(philo->table->start_time),
			philo->id, str);
	}
	else if (death >= 1 && philo->table->suicide == 0)
	{
		printf("%lld %d died\n", (long long)timediff(philo->table->start_time),
			philo->id);
		philo->table->suicide = 1;
	}
	pthread_mutex_unlock(&philo->table->rdwr);
	return (death);
}
