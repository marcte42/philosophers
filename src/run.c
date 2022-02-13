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

void	print_message(int message, t_philo *philo)
{
	t_time	time;

	gettimeofday(&time, NULL);
	if (philo->data->stop)
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (message == EAT)
		printf("\e[1;32m%ld %d is eating\e[0m\n", time_ms(philo->data->start_time), philo->id + 1);
	if (message == SLEEP)
	{
		printf("\e[1;33m%ld %d is sleeping\e[0m\n", time_ms(philo->data->start_time), philo->id + 1);
		philo->data->meals_count++;
	}
	if (message == THINK)
		printf("\e[1;35m%ld %d is thinking\e[0m\n", time_ms(philo->data->start_time), philo->id + 1);
	if (message == DEAD)
		printf("\e[0;31m%ld %d died\e[0m\n", time_ms(philo->data->start_time), philo->id + 1);
	if (message == FORK)
		printf("\e[1;34m%ld %d has taken a fork\e[0m\n", time_ms(philo->data->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	forks(int action, t_philo *philo)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
		pthread_mutex_lock(philo->right_fork);
		print_message(FORK, philo);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	philo_eat(t_philo *philo)
{
	print_message(THINK, philo);
	forks(LOCK, philo);
	print_message(EAT, philo);
	philo->last_eat = get_ms();
	usleep(philo->data->args[EAT_TIME] * 1000);
	forks(UNLOCK, philo);
}

void	philo_sleep(t_philo *philo)
{
	print_message(SLEEP, philo);
	usleep(philo->data->args[SLEEP_TIME] * 1000);
}

void	*run(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(400);
	i = -1;
	while (++i != philo->data->args[MAX_MEALS])
	{
		if (philo->data->stop == 1)
			return (0);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (0);
}
