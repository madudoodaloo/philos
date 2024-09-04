/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:10:30 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/04 13:08:37 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t ft_atoi(const char *str)
{
    size_t nbr;
    int i;

    nbr = 0;
    i = 0;
    while (str[i])
        nbr = 10 * nbr + (str[i++] - 48);
    //printf("%s is %ld\n", str, nbr);
    return(nbr);
}

void parser(t_args *args, char **av)
{
    args->n_philo = ft_atoi(av[1]);
    args->t_die = ft_atoi(av[2]);
    args->t_eat = ft_atoi(av[3]);
    args->t_sleep = ft_atoi(av[4]);
    if (av[5])
        args->n_eat = ft_atoi(av[5]);
}

int wrong_args(int ac, char **av)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (ac < 5 || ac > 6)
        return(printf("Bad arguments, expected 5 or 6.\n"));
    while (--ac)
    {
        while (av[ac][i])
        {
            if (av[ac][i] < 48 || av[ac][i++] > 57)
                return(printf("Bad arguments, only digits allowed\n"));
            else if (av[ac][0] == 48 && !flag)
            {
                while (av[ac][i] == 48 && av[ac][i])
                    i++;
                if (!av[ac][i])
                    return(printf("All args should be positive\n"));
                flag = 1;
            }
        }   
        i = 0;
        flag = 0;
    }
    return(0);
}
