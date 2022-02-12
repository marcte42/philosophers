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

	pthread_mutex_lock(&philo->data->print);
	gettimeofday(&time, DST_NONE);
	if (message == EAT)
		printf("%ld %d is eating\n", (time.tv_sec * 1000 + time.tv_usec) / 1000, philo->id + 1);
	if (message == SLEEP)
		printf("%ld %d is sleeping\n", (time.tv_sec * 1000 + time.tv_usec) / 1000, philo->id + 1);
	if (message == THINK)
		printf("%ld %d is thinking\n", (time.tv_sec * 1000 + time.tv_usec) / 1000, philo->id + 1);
	if (message == DEAD)
		printf("%ld %d died\n", (time.tv_sec * 1000 + time.tv_usec) / 1000, philo->id + 1);
	if (message == FORK)
		printf("%ld %d has taken a fork\n", (time.tv_sec * 1000 + time.tv_usec) / 1000, philo->id + 1);
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

void	eat(t_philo *philo)
{
	forks(LOCK, philo);
	print_message(EAT, philo);
	gettimeofday(&philo->last_eat, DST_NONE);
	usleep(philo->data->args[EAT] * 1000);
	forks(UNLOCK, philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_message(SLEEP, philo);
	usleep(philo->data->args[SLEEP] * 1000);
	print_message(THINK, philo);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(400);
	while (1)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (0);
}
