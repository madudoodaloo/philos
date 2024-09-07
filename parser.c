/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:45:54 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/07 17:24:28 by msilva-c         ###   ########.fr       */
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
int ft_skipspace(int ac, char **av)
{
    int i;
    
    i = 0;
    while (av[ac][i] == 48 && av[ac][i])
        i++;
    if (!av[ac][i])
        return(printf("Bad arguments, must be positive\n"));
    return (1);
}

int wrong_args(int ac, char **av)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (--ac)
    {
        while (av[ac][i])
        {
            if (av[ac][i] < 48 || av[ac][i++] > 57)
                return(printf("Bad arguments, only digits allowed\n"));
            else if (av[ac][0] == 48 && !flag)
            {
                flag = ft_skipspace(ac, av);
                if (flag > 1)
                    return (1);
            }
        }   
        i = 0;
        flag = 0;
    }
    return(0);
}
