/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:18:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/14 19:15:18 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*get_forks(t_philo *philo, int i)
{
	if (philo->args.n_philo == 1)
		return (NULL);
	else if (i + 1 == philo->args.n_philo)
		return (&philo->table->forks[0]);
	else
		return (&philo->table->forks[i + 1]);
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
		printf("left: [%p] right: [%p] philo: [%d]\n", philo[i].left_fork,
			philo[i].right_fork, i);
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
	while (!check_dead(philo))
	{
		i = split_eat(philo);
		if (!i)
			break ;
		if (philo->args.n_eat > 0 && philo->had_x_meals >= philo->args.n_eat
			&& i >= philo->args.n_eat * philo->args.n_philo)
			break ;
		if (print(0, philo, "is sleeping"))
			break ;
		ft_usleep(philo, philo->args.t_sleep);
		if (print(0, philo, "is thinking"))
			break ;
	}
	return (NULL);
}
