/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:59 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 17:26:29 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	int		j;

	data = arg;
	j = -1;
	while (++j != data->args[MAX_MEALS])
	{
		i = -1;
		while (++i < data->args[NB_PHILOS])
		{
			if (elapsed_time_since(data->philos[i].last_eat) > data->args[DIE_TIME])
			{
				print_message(DEAD, &data->philos[i]);
				data->stop = 1;
				return (NULL);
			}
			usleep(50);
		}
	}
	return (NULL);
}
