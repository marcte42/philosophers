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
	if (philo->data->args[NB_PHILOS] == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(FORK, philo);
		while (!philo->data->stop)
			;
		return ;
	}
	forks(LOCK, philo);
	print_message(EAT, philo);
	usleep(philo->data->args[EAT_TIME] * 1000);
	forks(UNLOCK, philo);
}

void	philo_sleep(t_philo *philo)
{
	print_message(SLEEP, philo);
	usleep(philo->data->args[SLEEP_TIME] * 1000);
	print_message(THINK, philo);
}

void	*run(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->args[DIE_TIME]);
	i = -1;
	while (++i != philo->data->args[MAX_MEALS])
	{
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->print);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->print);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (0);
}
