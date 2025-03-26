/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:56 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/25 20:48:23 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean_up(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(table->philosophers[i].thread, NULL) != 0)
			printf("Error: Failed to join thread %d\n", i);
	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_mutex_destroy(&table->forks[i].lock) != 0)
			printf("Error: Failed to destroy fork mutex %d\n", i);
		if (pthread_mutex_destroy(&table->forks[i].in_use_lock) != 0)
			printf("Error: Failed to destroy in_use_lock mutex %d\n", i);
		if (pthread_mutex_destroy(&table->philosophers[i].lte_lock) != 0)
			printf("Error: Failed to destroy last_time_eaten_loc mutex %d\n",
				i);
	}
	if (pthread_mutex_destroy(&table->write_lock) != 0)
		printf("Error: Failed to destroy write_lock mutex %d\n", i);
	if (pthread_mutex_destroy(&table->simulation_lock) != 0)
		printf("Error: Failed to destroy simulation_lock mutex %d\n", i);
	if (pthread_mutex_destroy(&table->eating_lock) != 0)
		printf("Error: Failed to destroy eating_lock mutex %d\n", i);
	free(table->philosophers);
	free(table->forks);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (input_validation(argc, argv) != 0)
		return (-1);
	if (init_table(argv, &table) == -1)
		return (printf("Malloc error"), -1);
	init_philosophers_and_forks(argv, &table);
	start_simulation(&table, argv);
	clean_up(&table);
}

static void	print_usage_error(void)
{
	printf("Error: expected four or five parameters:\n"
		"(num_of_philosophers)\n"
		"(time_to_die)\n"
		"(time_to_eat)\n"
		"(time_to_sleep)\n"
		"optional: [number_of_times_each_philosopher_must_eat]\n");
}

int	input_validation(int argc, char **argv)
{
	int	i;
	int	y;

	if (argc != 5 && argc != 6)
	{
		print_usage_error();
		return (-1);
	}
	i = 0;
	while (argv[++i] != NULL)
	{
		y = -1;
		while (argv[i][++y] != '\0')
		{
			if (!(argv[i][y] >= '0' && argv[i][y] <= '9'))
				return (printf("Error: Input should contain only digits.\n"),
					-2);
		}
		if (str_len(argv[i]) > 11)
			return (printf("Error: Value %s is too big", argv[i]), -3);
		if (ft_strncmp("00000000000", argv[i], 11) >= 0)
			return (printf("Error: Value %s has to be > 0", argv[i]), -4);
	}
	return (0);
}
