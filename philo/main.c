/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:56 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/22 15:46:38 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (input_validation(argc, argv) != 0)
		return (-1);
	if (init_table(argv, &table) == -1)
		printf("Malloc error");
	init_philosophers_and_forks(argv, &table);
	start_simulation(&table, argv);
	
	// clean_up() to do
}
int	input_validation(int argc, char **argv)
{
	int	i;
	int	y;

	if (argc != 5 && argc != 6)
	{
		printf("Error: expected four or five parameters:\n(number_of_philosophers)\n(time_to_die)\n(time_to_eat)\n"
				"(time_to_sleep)\noptional: [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	i = 0;
	while (argv[++i] != NULL)
	{
		y = -1;
		while (argv[i][++y] != '\0')
		{
			if (!(argv[i][y] >= '0' && argv[i][y] <= '9'))
				return (printf("Error: Input should contain only digits (0-9).\n"),
					-2);
		}
		if (str_len(argv[i]) > 11)
			return (printf("Error: Value %s is too big", argv[i]),-3);
		if (ft_strncmp("00000000000", argv[i], 11) >= 0)
			return (printf("Error: Value %s has to be > 0", argv[i]), -4);
	}
	return (0);
}
