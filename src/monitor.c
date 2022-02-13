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

void	monitoring(t_data *data)
{
	int		i;

	while (data->args[MAX_MEALS] != 0)
	{
		i = -1;
		while (++i < data->args[NB_PHILOS])
		{
			if (time_ms(data->philos[i].last_eat)
				> (unsigned long)data->args[DIE_TIME])
			{
				print_message(DEAD, &data->philos[i]);
				data->stop = 1;
				return ;
			}
			usleep(50);
		}
	}
}
