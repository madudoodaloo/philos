/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:33:16 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/12 14:52:11 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				n_eat;
}					t_args;

typedef struct s_table
{
	int				mutex_error;
	int				total_meals;
	pthread_mutex_t	meal_counter;
	int				dead;
	pthread_mutex_t	death;
	pthread_mutex_t	rdwr;
	pthread_mutex_t	*forks;
	long long		start_time;
}					t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	size_t			t_last_meal;
	int				had_x_meals;
	t_args			args;
	t_table			*table;
}					t_philo;

/* parser.c */
size_t				ft_atoi(const char *str);
int					wrong_args(int ac, char **av);

/* init.c */
int					free_and_exit(t_table *table, t_philo *philo, char *str);
t_args				init_args(char **av);
t_table				*init_table(t_args args);
t_philo				*init_philo(t_args args, t_table *table);

/* time.c */
void 				ft_usleep(long long time_to);
long long			timediff(long long start);
long long			gettimems(void);

/* threads.c */
int	eat_impar(t_philo *philo);
int	eat_par(t_philo *philo);
int	print(int death, t_philo *philo, char *str);
int					eat(t_philo *philo);
int					check_dead(t_philo *philo);
void				*alive(void *args);
int					simulation(t_philo *philo, t_args args, t_table *table);

#endif
