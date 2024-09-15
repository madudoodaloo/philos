/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:12:45 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/15 04:02:47 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	drop_forks(pthread_mutex_t *first, pthread_mutex_t *last)
{
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(last);
	return (0);
}

int	eat_odd(t_philo *philo)
{
	if (print(0, philo, NULL))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (print(0, philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork));
	pthread_mutex_lock(philo->left_fork);
	philo->t_last_meal = gettimems();
	if (print(0, philo, "has taken a fork"))
		return (drop_forks(philo->left_fork, philo->right_fork));
	print(0, philo, "is eating");
	if (ft_usleep(philo, philo->args.t_eat) > 0)
		return (drop_forks(philo->left_fork, philo->right_fork));
	philo->had_x_meals++;
	drop_forks(philo->left_fork, philo->right_fork);
	return (countmeal(philo, 1));
}

int	eat_even(t_philo *philo)
{
	if (print(0, philo, NULL))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (print(0, philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork));
	pthread_mutex_lock(philo->right_fork);
	philo->t_last_meal = gettimems();
	if (print(0, philo, "has taken a fork"))
		return (drop_forks(philo->right_fork, philo->left_fork));
	print(0, philo, "is eating");
	if (ft_usleep(philo, philo->args.t_eat) > 0)
		return (drop_forks(philo->right_fork, philo->left_fork));
	philo->had_x_meals++;
	drop_forks(philo->right_fork, philo->left_fork);
	return (countmeal(philo, 1));
}

int	split_eat(t_philo *philo)
{
	int	ret;

	ret = 1;
	if (philo->id % 2 == 1)
		ret = eat_odd(philo);
	else
		ret = eat_even(philo);
	return (ret);
}

void	*table_for_one(t_philo *philo)
{
	print(0, philo, "has taken a fork");
	unsync(philo->args.t_die);
	printf("%lld %d died\n", timediff(philo->table->start_time), philo->id);
	return (NULL);
}
