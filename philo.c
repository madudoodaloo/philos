/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:13:00 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 17:49:15 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table *table;

    if (ac != 5 && ac != 6)
        return(printf("Wrong number of args\n"));
    if (!check_args(ac, av))
        return 0;
    table = (t_table *)malloc(sizeof(t_table));
    if (!table || !init_all(table, av))
        free_and_exit(table, "Malloc failed");    
    simulation(table, table->args, table->philo);
    if (table->start_time < 0)
        return (1);
    return(free_and_exit(table, ""));
}
