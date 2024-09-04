/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:53:37 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 15:07:43 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *init_all(t_table *table, char **av)
{
	table = (t_table *)malloc(sizeof(t_table));
	if(!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->n_philo = ft_atoi(av[1]);
	table->philo = (t_philo **)malloc(sizeof(t_philo *) * table->n_philo);
	if (!table->philo)
		return(table);
	memset(table->philo, 0, sizeof(t_philo));
	table->args = (t_args *)malloc(sizeof(t_args));
	if (!table->args)
		return (table);
	parser(&table->args, av);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (table->n_philo + 1));
		return(table);
	int i = -1;
	while (++i < table->n_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	return(table);
}

int free_and_exit(t_table *table, char *str)
{
	int i;

	i = -1;
	if (table->philo)
		free(&table->philo);
	if(table)
	{
    	pthread_mutex_destroy(&table->rdwr);
		if (table->forks)
		{
			while (++i < table->n_philo)
				pthread_mutex_destroy(&table->forks[i]);
			free(&table->forks);
		}
	}
	if (str)
		return(printf("%s\n", str));
	return (0);
}

int main(int ac, char **av)
{
	t_table	*table;
	int ret;

	ret = 0;
	table = NULL;
    if(!wrong_args(ac, av))
    {
		table = init_all(table, av);
        if(table && table->philo && table->args)
        {
			ret = set_table(table, &table->philo, av);
        }
		else
    		return(free_and_exit(table, "Failed malloc"));
    }
	if(!ret)
    	return (free_and_exit(table, NULL));
}
