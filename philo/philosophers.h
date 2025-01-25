/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:46:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/25 16:49:54 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <libc.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
// structs//
typedef struct s_fork
{
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	int				index;
	long			times_eaten;
	t_fork			*fork_left;
	t_fork			*fork_right;
	bool			is_dead;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			number_of_meals;
	long			last_time_eaten;
	long			start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	last_time_eaten_lock;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_mutex_t	simulation_lock;
	bool			stop_simulation;
}					t_table;

int					input_validation(int argc, char **argv);
long				ft_atol(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					str_len(char *str);
int					init_table(char **argv, t_table *table);
void				init_philosophers_and_forks(char **argv, t_table *table);
long				current_time_in_ms(void);
void				start_simulation(t_table *table, char **argv);
void				*philo_routine(void *arg);
void				print_action(t_philo *philo, char *action);
void				eating(t_philo	*philo);
void				thinking(t_philo	*philo);
int					reaper(t_philo		*philo);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
#endif