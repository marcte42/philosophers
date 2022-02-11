/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:54:59 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 17:26:29 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_data *data)
{
	int	i;
	data->philos = ft_calloc(data->vars[0], sizeof(t_philo));
	if (!data->philos)
		return (0);
	data->forks = ft_calloc(data->vars[0], sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->vars[NB_PHILOS])
	{
		data->philos[i].id = i + 1;
		if (pthread_create(&data->philos[i].thread, NULL, &run, &data->philos[i]))
			return (0);
	}
	i = -1;
	while (++i < data->vars[NB_PHILOS])
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
	return (1);
}
