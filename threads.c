/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:18:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/11 13:51:17 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_odd(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a left fork");
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (check_dead(philo))
		return (1);
	philo->t_last_meal = gettimems();
	print(philo, "has taken a right fork");
	print(philo, "is eating");
	philo->had_x_meals++;
	wait_now(philo, philo->args.t_eat);
	if (check_dead(philo))
		return (1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (check_dead(philo));
}

int	eat(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a right fork");
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (check_dead(philo))
		return (1);
	philo->t_last_meal = gettimems();
	print(philo, "has taken a left fork");
	print(philo, "is eating");
	philo->had_x_meals++;
	wait_now(philo, philo->args.t_eat);
	if (check_dead(philo))
		return (1);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (check_dead(philo));
}

void	*table_for_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	while (1)
	{
		if (check_dead(philo))
			break ;
	}
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*alive(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	//printf("%d has entered routine\n", philo->id);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->t_last_meal = gettimems();
	if (philo->args.n_philo == 1)
		return (table_for_one(philo));
	while (!check_dead(philo))
	{
		if (philo->id % 2 == 0) {
			if (eat(philo))
				break ;
		} else {
			if (eat_odd(philo))
				break ;
		}
		if (philo->args.n_eat > 0 && philo->had_x_meals == philo->args.n_eat)
			break ;
		if (check_dead(philo))
			break ;
		print(philo, "is sleeping");
		wait_now(philo, philo->args.t_sleep);
		if (check_dead(philo))
			break ;
		print(philo, "is thinking");
	}
	return (NULL);
}

int	simulation(t_philo *philo, t_args args, t_table *table)
{
	int	i;

	table->start_time = gettimems();
	if (table->start_time < 0)
		return (free_and_exit(table, philo, "gettimeof() error"));
	i = -1;
	while (++i < args.n_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &table->forks[i];
		if (args.n_philo == 1)
			philo[i].right_fork = NULL;
		else
			philo[i].right_fork = &table->forks[(i + 1) % args.n_philo];
		printf("left: [%p] right: [%p] philo: [%d]\n", philo[i].left_fork, philo[i].right_fork, i);

	}
	i = -1;
	while (++i < args.n_philo)
		if (pthread_create(&philo[i].thread, NULL, &alive, &philo[i]))
			return (free_and_exit(table, philo, "error creating thread"));
	i = -1;
	while (++i < args.n_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (free_and_exit(table, philo, "error joining thread"));
	}
	return (0);
}
