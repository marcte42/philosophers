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
	int		i;
	t_data	*data;

	data = arg;
	while (data->args[MAX_MEALS])
	{
		i = -1;
		while (++i < data->args[NB_PHILOS])
		{
			pthread_mutex_lock(&data->print);
			if (data->meals_count == data->args[NB_PHILOS] * data->args[MAX_MEALS])
			{
				pthread_mutex_unlock(&data->print);
				return (NULL);
			}
			else if (time_ms(data->philos[i].last_eat)
				> (unsigned long)data->args[DIE_TIME])
			{
				data->stop = 1;
				printf("\e[0;31m%ld %d died\e[0m\n", time_ms(data->start_time), data->philos[i].id + 1);
				pthread_mutex_unlock(&data->print);
				return (NULL);
			}
			pthread_mutex_unlock(&data->print);
			usleep(40);
		}
	}
	return (NULL);
}
