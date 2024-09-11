/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:50 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/10 20:06:29 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atoi(const char *str)
{
	size_t	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (str[i])
		nbr = 10 * nbr + (str[i++] - 48);
	return (nbr);
}



int	wrong_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"));
	while (--ac)
	{
		while (av[ac][i])
		{
			if (av[ac][i] < 48 || av[ac][i++] > 57)
				return (printf("Bad arguments, only digits allowed\n"));
		}
		i = 0;
	}
	return (0);
}
