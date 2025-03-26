/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:07 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/26 13:29:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	long	start_time_to_sleep;

	print_action(philo, "is sleeping");
	start_time_to_sleep = current_time_in_ms();
	while (current_time_in_ms() - start_time_to_sleep < philo->time_to_sleep)
	{
		if (reaper(philo) == 1)
			return ;
		usleep(1000);
	}
}

static int	handle_one_philo(t_philo *philo)
{
	if (philo->table->philo_count < 2)
	{
		pthread_mutex_unlock(&philo->fork_left->lock);
		usleep(philo->time_to_die * 1000);
		return (-1);
	}
	return (0);
}

static int	pick_up_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork_right->in_use_lock);
		if (philo->fork_right->in_use == false)
		{
			pthread_mutex_lock(&philo->fork_right->lock);
			print_action(philo, "has taken a fork");
			philo->fork_right->in_use = true;
			pthread_mutex_unlock(&philo->fork_right->in_use_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->fork_right->in_use_lock);
		if (reaper(philo) == 1)
		{
			pthread_mutex_unlock(&philo->fork_left->lock);
			return (-2);
		}
		usleep(1000);
	}
	return (0);
}

static int	picking_up_the_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork_left->in_use_lock);
		if (philo->fork_left->in_use == false)
		{
			pthread_mutex_lock(&philo->fork_left->lock);
			print_action(philo, "has taken a fork");
			philo->fork_left->in_use = true;
			pthread_mutex_unlock(&philo->fork_left->in_use_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->fork_left->in_use_lock);
		if (reaper(philo) == 1)
			return (-2);
		usleep(1000);
	}
	if (reaper(philo) == 1)
		return (pthread_mutex_unlock(&philo->fork_left->lock), -2);
	if (handle_one_philo(philo) == -1)
		return (-1);
	if (reaper(philo) == 1)
		return (pthread_mutex_unlock(&philo->fork_left->lock), -2);
	if (pick_up_right_fork(philo) < 0)
		return (-1);
	return (0);
}

void	eating(t_philo *philo)
{
	if (picking_up_the_forks(philo) < 0)
		return ;
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->lte_lock);
	philo->last_time_eaten = current_time_in_ms();
	pthread_mutex_unlock(&philo->lte_lock);
	while (current_time_in_ms() - philo->last_time_eaten < philo->time_to_eat)
	{
		if (reaper(philo) == 1)
			return (pthread_mutex_unlock(&philo->fork_left->lock),
				pthread_mutex_unlock(&philo->fork_right->lock), (void)0);
		usleep(1000);
	}
	pthread_mutex_lock(&philo->fork_left->in_use_lock);
	philo->fork_left->in_use = false;
	pthread_mutex_unlock(&philo->fork_left->in_use_lock);
	pthread_mutex_lock(&philo->fork_right->in_use_lock);
	philo->fork_right->in_use = false;
	pthread_mutex_unlock(&philo->fork_right->in_use_lock);
	pthread_mutex_unlock(&philo->fork_left->lock);
	pthread_mutex_unlock(&philo->fork_right->lock);
	philo->times_eaten++;
}
