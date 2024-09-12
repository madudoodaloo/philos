/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:18:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/12 16:48:02 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int countmeal(t_philo *philo, int flag)
{
	int	i;

	pthread_mutex_lock(&philo->table->meal_counter);
	if (flag)
		philo->table->total_meals++;
	i = philo->table->total_meals;
	pthread_mutex_unlock(&philo->table->meal_counter);
	return (i);
}
int	eat_impar(t_philo *philo)
{
	if (print(check_dead(philo), philo, NULL))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (print(check_dead(philo), philo, "has taken a right fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print(check_dead(philo), philo, "has taken a left fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print(0, philo, "is eating");
	philo->t_last_meal = gettimems();
	ft_usleep(philo->args.t_eat);
	philo->had_x_meals++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (countmeal(philo, 1));
}

int	eat_par(t_philo *philo)
{
	if (print(check_dead(philo), philo, NULL))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (print(check_dead(philo), philo, "has taken a left fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print(check_dead(philo), philo, "has taken a right fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print(0, philo, "is eating");
	philo->t_last_meal = gettimems();
	ft_usleep(philo->args.t_eat);
	philo->had_x_meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (countmeal(philo, 1));
}

int	split_eat(t_philo *philo)
{
	int	ret;

	ret = 1;
	if (philo->id % 2)
		ret = eat_impar(philo);
	else
		ret = eat_par(philo);
	return (ret);
}

void	*table_for_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(0, philo, "has taken a fork");
	while (1)
	{
		if (check_dead(philo))
		{
			print(1, philo, "died");
			break ;
		}
	}
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*alive(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	philo->t_last_meal = gettimems();
	if (philo->args.n_philo == 1)
		return (table_for_one(philo));
	while (!check_dead(philo))
	{
		int i = split_eat(philo);
		if (!i)
			break ;
		if (philo->args.n_eat > 0 && philo->had_x_meals >= philo->args.n_eat \
			&& i >= philo->args.n_eat * philo->args.n_philo)
			break ;
		if (print(check_dead(philo), philo, "is sleeping"))
			break ;
		ft_usleep(philo->args.t_sleep);
		if (print(check_dead(philo), philo, "is thinking"))
			break ;
	}
	return (NULL);
}

static pthread_mutex_t	*get_forks(t_philo *philo, int i)
{
	if (philo->args.n_philo == 1)
		return (NULL);
	else if (i + 1 == philo->args.n_philo)
		return (&philo->table->forks[0]);
	else
		return (&philo->table->forks[i + 1]);
}

int	simulation(t_philo *philo, t_args args, t_table *table)
{
	int	i;

	table->start_time = gettimems();
	if (table->start_time < 0)
		return (free_and_exit(table, philo, "gettimeof() error"));
	i = -1;
	while (++i < args.n_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = get_forks(&philo[i], i);
		printf("left: [%p] right: [%p] philo: [%d]\n", philo[i].left_fork,
				philo[i].right_fork, i);
	}
	i = -1;
	while (++i < args.n_philo)
		if (pthread_create(&philo[i].thread, NULL, &alive, &philo[i]))
			return (free_and_exit(table, philo, "error creating thread"));
	i = -1;
	while (++i < args.n_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (free_and_exit(table, philo, "error joining thread"));
	}
	return (0);
}
