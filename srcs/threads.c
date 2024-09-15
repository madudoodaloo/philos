/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:18:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/15 04:08:53 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*alive(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)args;
	philo->t_last_meal = philo->table->start_time;
	if (philo->args.n_philo == 1)
		return (table_for_one(philo));
	if (philo->id % 2 == 0)
		unsync(10);
	while (1)
	{
		i = split_eat(philo);
		if (!i)
			break ;
		if (philo->args.n_eat > 0 && philo->had_x_meals >= philo->args.n_eat \
			&& i >= philo->args.n_eat * philo->args.n_philo)
			break ;
		if (print(0, philo, "is sleeping"))
			break ;
		if (ft_usleep(philo, philo->args.t_sleep))
			break ;
		if (print(0, philo, "is thinking"))
			break ;
	}
	return (NULL);
}

pthread_mutex_t	*get_forks(t_philo *philo, int i)
{
	if (philo->args.n_philo == 1)
		return (NULL);
	else if (i + 1 == philo->args.n_philo)
		return (&philo->table->forks[0]);
	else
		return (&philo->table->forks[i + 1]);
}

void	*monitor(void *args)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = (t_philo **)args;
	while (philo[0]->args.n_philo != 1)
	{
		i = 0;
		while (i < philo[i]->args.n_philo)
		{
			pthread_mutex_lock(&philo[0]->table->monitor);
			if ((gettimems() - philo[i]->table->start_time) > \
				(long long)philo[0]->args.t_die)
			{
				pthread_mutex_unlock(&philo[0]->table->monitor);
				print(1, philo[i], NULL);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[0]->table->monitor);
			i++;
		}
		usleep(100);
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
		philo[i].right_fork = get_forks(&philo[i], i);
	}
	i = -1;
	while (++i < args.n_philo)
		if (pthread_create(&philo[i].thread, NULL, &alive, &philo[i]))
			return (free_and_exit(table, philo, "error creating thread"));
	pthread_create(&table->th_monitor, NULL, &monitor, &philo);
	i = -1;
	while (++i < args.n_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (free_and_exit(table, philo, "error joining thread"));
	}
	pthread_join(table->th_monitor, NULL);
	return (0);
}
