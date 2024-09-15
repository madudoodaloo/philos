/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:33:16 by msilva-c          #+#    #+#             */
/*   Updated: 2024/09/14 21:29:02 by msilva-c         ###   ########.fr       */
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
	pthread_mutex_t monitor;
	pthread_mutex_t	death;
	pthread_mutex_t	rdwr;
	pthread_mutex_t	*forks;
	pthread_t		th_monitor;
	long long		start_time;
	int				suicide;
}					t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		t_last_meal;
	int				had_x_meals;
	t_args			args;
	t_table			*table;
}					t_philo;

/* eat.c */
int					drop_forks(pthread_mutex_t *first, pthread_mutex_t *last);
int					eat_odd(t_philo *philo);
int					eat_even(t_philo *philo);
int					split_eat(t_philo *philo);
void				*table_for_one(t_philo *philo);

/* init.c */
int					free_and_exit(t_table *table, t_philo *philo, char *str);
t_args				init_args(char **av);
t_table				*init_table(t_args args);
t_philo				*init_philo(t_args args, t_table *table);

/* parser.c */
size_t				ft_atoi(const char *str);
int					wrong_args(int ac, char **av);

/* time.c */
void				unsync(long long time_to);
int					ft_usleep(t_philo *philo, long long time_to);
long long			timediff(long long start);
long long			gettimems(void);

/* threads.c */
pthread_mutex_t		*get_forks(t_philo *philo, int i);
int					simulation(t_philo *philo, t_args args, t_table *table);
void				*alive(void *args);

/* utils.c */
int					countmeal(t_philo *philo, int flag);
int					check_dead(t_philo *philo);
int					print(int death, t_philo *philo, char *str);
#endif
