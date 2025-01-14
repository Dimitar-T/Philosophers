/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:56 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/13 19:25:47 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (input_validation(argc, argv) != 0)
		return (-1);
	else
		printf("great succec");
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
				return(printf("Error: The input should contain only digits (0-9).\n"), -2);
		}	
	}
	return (0);
}

int is_positive_num(int argc, char **argv)
{
	int	i;
	int	y;

	i = 0;
	while (argc > 1)
	{
		if (argv[i])
		{
			/* code */
		}
		
	}
	
}
