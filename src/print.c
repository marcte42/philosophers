/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:05:53 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 17:28:23 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int message, t_philo *philo)
{
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (message == EAT)
	{
		printf("\e[1;32m%ld %d is eating\e[0m\n",
			time_ms(philo->data->start_time), philo->id + 1);
		philo->last_eat = get_ms();
	}
	if (message == SLEEP)
	{
		printf("\e[1;33m%ld %d is sleeping\e[0m\n",
			time_ms(philo->data->start_time), philo->id + 1);
		philo->data->meals_count++;
	}
	if (message == THINK)
		printf("\e[1;35m%ld %d is thinking\e[0m\n",
			time_ms(philo->data->start_time), philo->id + 1);
	if (message == FORK)
		printf("\e[1;34m%ld %d has taken a fork\e[0m\n",
			time_ms(philo->data->start_time), philo->id + 1);
}

void	print_message(int message, t_philo *philo)
{
	t_time	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->data->print);
	print_action(message, philo);
	pthread_mutex_unlock(&philo->data->print);
}
