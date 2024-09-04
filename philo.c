/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:53:37 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 12:29:33 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *init_all(t_table *table, int ac, char **av)
{
	table = (t_table *)malloc(sizeof(t_table));
	if(!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->n_philo = ft_atoi(av[1]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return(table);
	memset(table->philo, 0, sizeof(t_philo));
	return(table);
}

void free_and_exit(t_table *table, char *str)
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
		printf("%s\n", str);
}

int main(int ac, char **av)
{
	t_table	*table;
    pthread_t *threads;

	table = NULL;
    if(!wrong_args(ac, av))
    {
		table = init_all(table, ac, av);
        if(table && table->philo)
        {
			set_table(table, &table->philo);
            threads = create_philo(table, table->philo->n_philo);
        }
		else
    		free_and_exit(table, "Failed malloc");
    }
    free_and_exit(table, NULL);
    return (0);
}
