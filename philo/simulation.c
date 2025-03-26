/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:34 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/26 13:34:45 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_table *table, char **argv)
{
	int		i;
	long	time;

	i = -1;
	time = current_time_in_ms();
	while (++i < ft_atol(argv[1]))
	{
		table->philosophers[i].start_time = time;
		table->philosophers[i].last_time_eaten = time;
		if (pthread_create(&table->philosophers[i].thread, NULL, philo_routine,
				&table->philosophers[i]) != 0)
		{
			printf("Error: Pthread_create failled");
			return ;
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->number_of_meals != philo->times_eaten)
	{
		if (philo->index % 2 != 0 && philo->first_iteration++ == 0
			&& philo->table->philo_count > 1)
			usleep(philo->time_to_eat * 500);
		if (reaper(philo) == 1)
			break ;
		eating(philo);
		if (philo->number_of_meals == philo->times_eaten)
		{
			pthread_mutex_lock(&philo->table->eating_lock);
			philo->table->philos_that_are_done_eating++;
			pthread_mutex_unlock(&philo->table->eating_lock);
		}
		if (reaper(philo) == 1)
			break ;
		sleeping(philo);
		if (reaper(philo) == 1)
			break ;
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int	reaper(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->simulation_lock);
	pthread_mutex_lock(&philo->lte_lock);
	if (philo->table->stop_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->simulation_lock);
		pthread_mutex_unlock(&philo->lte_lock);
		return (1);
	}
	else if ((current_time_in_ms()
			- philo->last_time_eaten) > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->simulation_lock);
		pthread_mutex_unlock(&philo->lte_lock);
		return (print_action(philo, "died"), 1);
	}
	pthread_mutex_unlock(&philo->lte_lock);
	pthread_mutex_unlock(&philo->table->simulation_lock);
	pthread_mutex_lock(&philo->table->eating_lock);
	if (philo->table->philos_that_are_done_eating == philo->table->philo_count)
	{
		pthread_mutex_unlock(&philo->table->eating_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eating_lock);
	return (0);
}

void	print_action(t_philo *philo, char *action)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->simulation_lock);
	if (philo->table->stop_simulation)
	{
		pthread_mutex_unlock(&philo->table->simulation_lock);
		return ;
	}
	if (ft_strncmp(action, "died", 4) == 0)
		philo->table->stop_simulation = true;
	pthread_mutex_lock(&philo->table->write_lock);
	time_stamp = current_time_in_ms() - philo->start_time;
	printf("%ld %d %s\n", time_stamp, philo->index, action);
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_unlock(&philo->table->simulation_lock);
}
