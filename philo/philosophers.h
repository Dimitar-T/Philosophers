/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:46:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/25 19:48:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

//---------structs---------//
typedef struct s_fork
{
	pthread_mutex_t	lock;
	bool			in_use;
	pthread_mutex_t	in_use_lock;
}					t_fork;

typedef struct s_philo
{
	int				index;
	int				first_iteration;
	long			times_eaten;
	t_fork			*fork_left;
	t_fork			*fork_right;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			number_of_meals;
	long			last_time_eaten;
	long			start_time;
	pthread_mutex_t	lte_lock;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	eating_lock;
	int				philos_that_are_done_eating;
	t_philo			*philosophers;
	t_fork			*forks;
	long			philo_count;
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	write_lock;
	bool			stop_simulation;
}					t_table;
//---------end_of_structs---------//

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
void				sleeping(t_philo	*philo);
int					reaper(t_philo *philo);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
