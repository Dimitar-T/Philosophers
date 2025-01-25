/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:26:33 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/24 15:56:07 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_table(char **argv, t_table *table)
{
	table->philosophers = malloc(sizeof(t_philo) * ft_atol(argv[1]));
	if (table->philosophers == NULL)
		return (-1);
	table->forks = malloc(sizeof(t_philo) * ft_atol(argv[1])); 
	if (table->forks == NULL)
	{
		free(table->philosophers); 
		return (-1);
	}
	pthread_mutex_init(&table->philosophers->write_lock, NULL);
	pthread_mutex_init(&table->simulation_lock, NULL);
	table->stop_simulation = false;
	return (0);
}

void	init_philosophers_and_forks(char **argv, t_table *table)
{
	int	i;
	
	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		table->philosophers[i].index = i + 1;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].is_dead = false;
		table->philosophers[i].fork_left = &table->forks[i];
		if (i == 0)
			table->philosophers[i].fork_right = &table->forks[ft_atol(argv[1]) - 1];
		else
			table->philosophers[i].fork_right = &table->forks[i - 1];
		table->philosophers[i].time_to_eat = ft_atol(argv[3]);
		table->philosophers[i].time_to_sleep = ft_atol(argv[4]);
		table->philosophers[i].time_to_die = ft_atol(argv[2]);
		if (argv[5] != NULL)
			table->philosophers[i].number_of_meals = ft_atol(argv[5]);
		else
			table->philosophers[i].number_of_meals = -1;
		table->philosophers[i].last_time_eaten = 0;
		table->philosophers[i].table = table;
		pthread_mutex_init(&table->forks[i].lock, NULL);
		pthread_mutex_init(&table->philosophers[i].last_time_eaten_lock, NULL);
	}
}



