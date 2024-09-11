/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:37:14 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/10 15:56:00 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philo;
	t_table	*table;

	if (wrong_args(ac, av))
		return (0);
	args = init_args(av);
	table = init_table(args);
	philo = init_philo(args, table);
	if (!table || !philo || !table->forks)
		return (free_and_exit(table, philo, "malloc() failed"));
	else if (table->mutex_error)
		return (free_and_exit(table, philo, "pthread_mutex_init failed"));
	simulation(philo, args, table);
	return (free_and_exit(table, philo, NULL));
}
