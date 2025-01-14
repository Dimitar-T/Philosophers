/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:46:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/14 20:12:15 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <libc.h>
#include <pthread.h>

//structs//
typedef	struct s_fork
{
	pthread_mutex_t	lock;
	int				id;
} t_fork;

typedef	struct s_philo
{
	int		index;
	long	time_to_eat;
	long	times_eaten;
	long	time_to_sleep;
	long	time_to_die;
	void	*fork_left;
	void	*fork_right;
	
} t_philo;

int		input_validation(int argc, char **argv);
long	atol(char *str);
#endif