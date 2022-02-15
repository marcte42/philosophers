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

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args[NB_PHILOS])
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i;
		data->philos[i].last_eat = get_ms();
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].right_fork = &data->forks[data->args[NB_PHILOS] - 1];
		else
			data->philos[i].right_fork = &data->forks[i - 1];
		if (pthread_create(&data->philos[i].thread, NULL, &run, &data->philos[i]))
			return (0);
	}
	return (1);
}

int	init(t_data *data)
{
	int	i;

	data->philos = ft_calloc(data->args[0], sizeof(t_philo));
	if (!data->philos)
		return (0);
	data->forks = ft_calloc(data->args[0], sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	pthread_mutex_init(&data->print, NULL);
	data->start_time = get_ms();
	if (!init_philo(data))
		return (0);
	pthread_create(&data->monitor, NULL, &monitoring, data);
	i = -1;
	while (++i < data->args[NB_PHILOS])
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	i = -1;
	while (++i < data->args[NB_PHILOS])
		pthread_mutex_destroy(&data->forks[i]);
	free(data->philos);
	free(data->forks);
	return (1);
}
