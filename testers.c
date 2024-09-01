/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:11:02 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 03:11:19 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_struct(t_args *args)
{
    printf("av[] = %d\n", args->philos);
    printf("av[] = %ld\n", args->t_die);
    printf("av[] = %ld\n", args->t_eat);
    printf("av[] = %ld\n", args->t_sleep);
    printf("av[] = %d\n", args->x_eat);
}
