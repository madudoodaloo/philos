/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 03:11:02 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/01 16:18:43 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_struct(t_philo *args)
{
    printf("av[] = %d\n", args->n_philo);
    printf("av[] = %ld\n", args->t_die);
    printf("av[] = %ld\n", args->t_eat);
    printf("av[] = %ld\n", args->t_sleep);
    printf("av[] = %d\n", args->n_eat);
}
