/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:40:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/01/13 14:43:58 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	atol(char *str)
{
	int		i;
	int		is_min;
	long	result;
	int		sign_count;

	i = 0;
	is_min = 1;
	result = 0;
	sign_count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_min = -1;
		sign_count++;
		if (sign_count > 1)
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - 48;
	return (result * is_min);
}
