/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:38:48 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/14 19:37:07 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_and_exit(t_table *table, t_philo *philo, char *str)
{
	int	i;

	i = -1;
	if (table)
	{
		while (++i < philo->args.n_philo)
			if (pthread_mutex_destroy(&table->forks[i]))
				printf("failed to destroy [%d] fork mutex\n", i);
		free(table->forks);
		pthread_mutex_destroy(&table->death);
		pthread_mutex_destroy(&table->rdwr);
		pthread_mutex_destroy(&table->meal_counter);
		free(table);
	}
	if (philo)
		free(philo);
	if (str)
		return (printf("%s\n", str));
	return (0);
}

t_args	init_args(char **av)
{
	t_args	args;

	args.n_philo = ft_atoi(av[1]);
	args.t_die = ft_atoi(av[2]);
	args.t_eat = ft_atoi(av[3]);
	args.t_sleep = ft_atoi(av[4]);
	if (av[5] && ft_atoi(av[5]) != 0)
		args.n_eat = ft_atoi(av[5]);
	else
		args.n_eat = -1;
	return (args);
}

t_table	*init_table(t_args args)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	pthread_mutex_init(&table->meal_counter, NULL);
	pthread_mutex_init(&table->rdwr, NULL);
	pthread_mutex_init(&table->death, NULL);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args.n_philo);
	if (!table->forks)
		return (table);
	while (++i < args.n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			table->mutex_error = 1;
			break ;
		}
	}
	return (table);
}

t_philo	*init_philo(t_args args, t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * args.n_philo);
	if (!philo)
		return (NULL);
	while (++i < args.n_philo)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].args = args;
		philo[i].table = table;
	}
	return (philo);
}
