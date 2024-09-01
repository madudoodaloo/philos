/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:10:30 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 05:18:55 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_all(t_args *args)
{
    args->philos = 0;
    args->t_die = 0;
    args->t_eat = 0;
    args->t_sleep = 0;
    args->x_eat = 0;
}

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

void parser(char **av, t_args *args)
{
    args->philos = ft_atoi(av[1]);
    args->t_die = ft_atoi(av[2]);
    args->t_eat = ft_atoi(av[3]);
    args->t_sleep = ft_atoi(av[4]);
    if (av[5])
        args->x_eat = ft_atoi(av[5]);
}

int wrong_args(int ac, char **av)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (ac < 5)
        return(printf("Too few arguments, should be:\n[n_philos] [t_die] [t_eat] [t_sleep] [x_eat](optional)\n"));
    else if (ac > 6)
        return(printf("Too many arguments, check subject.\n"));
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
