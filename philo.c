/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:53:37 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 05:18:22 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_args *args;

    if(!wrong_args(ac, av))
    {
        args = (t_args *)malloc(sizeof(t_args));
        if(args)
        {
            init_all(args);
            parser(av, args);
            create_philo(args);
            //print_struct(args);
        }
        else
            return(printf("malloc problem\n"));
    }
    return (0);
}