/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:28:34 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/25 16:50:45 by dtrendaf         ###   ########.fr       */
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
		if (pthread_create(&table->philosophers[i].thread, NULL, philo_routine,
				&table->philosophers[i]) != 0)
		{
			printf("Error: Pthread_create failled");
			return ;
		}
		table->philosophers[i].last_time_eaten = time;
	}
	while (i >= 0)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i--;
	}
	
}

void	*philo_routine(void *arg)
{
	t_philo		*philo; 
	
	philo = (t_philo *)arg;
	while ((!philo->is_dead) && philo->number_of_meals != philo->times_eaten)
	{
		if(reaper(philo) == 1)
			break;
		thinking(philo);
		if(reaper(philo) == 1)
			break;
		eating(philo);
		if(reaper(philo) == 1)
			break;
		print_action(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}
int	reaper(t_philo		*philo)
{
	pthread_mutex_lock(&philo->table->simulation_lock);
		if (philo->table->stop_simulation == true)
		{
			pthread_mutex_unlock(&philo->table->simulation_lock);
			return (1);
		}
		else if ((current_time_in_ms() - philo->last_time_eaten)  > philo->time_to_die)
		{
			pthread_mutex_unlock(&philo->table->simulation_lock);
			print_action(philo, "has died");
			return (1);
		}
		pthread_mutex_unlock(&philo->table->simulation_lock);
	return (0);
}
void	thinking(t_philo	*philo)
{
	static int	first_iteration = 0;
	
	print_action(philo, "is thinking");
		if (philo->index % 2 != 0 && first_iteration == 0)
			usleep(philo->time_to_eat / 2);
		first_iteration = 1;
}
void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork_left->lock);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_right->lock);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_time_eaten_lock);
	philo->last_time_eaten = current_time_in_ms();
	pthread_mutex_unlock(&philo->last_time_eaten_lock);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork_left->lock);
	pthread_mutex_unlock(&philo->fork_right->lock);
	philo->times_eaten++;
}

void	print_action(t_philo *philo, char *action)
{
	long	time_stamp;
	
	pthread_mutex_lock(&philo->table->simulation_lock);
	if (philo->table->stop_simulation)
	{
		pthread_mutex_unlock(&philo->table->simulation_lock);
		return;
	}
	if (ft_strncmp(action, "has died", 9) == 0)
		philo->table->stop_simulation = true;
	pthread_mutex_unlock(&philo->table->simulation_lock);
	time_stamp = current_time_in_ms() - philo->start_time;
	pthread_mutex_lock(&philo->write_lock);
	printf("%ld %d %s\n",time_stamp, philo->index, action);
	pthread_mutex_unlock(&philo->write_lock);
}
