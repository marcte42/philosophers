/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:55:21 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 17:25:14 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

// State
# define EAT	0
# define SLEEP	1
# define THINK	2
# define DEAD	3
# define FORK	4

// Index of the parsed argument
# define NB_PHILOS	0
# define EAT_TIME	1
# define SLEEP_TIME	2
# define DIE_TIME	3
# define MAX_MEALS	4

// Mutex helper
# define LOCK		1
# define UNLOCK		0

typedef struct timeval t_time;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				state;					// State : EAT SLEEP THINK DEAD
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_time			last_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;				// Table of philosophers
	pthread_mutex_t	*forks;					// Table of forks (mutex)
	pthread_mutex_t	print;					// Mutex for printing on stdout
	int				args[5];				// 0:Number of philosophers 1:Time to eat 2:Time to eat 3:Time to tie 4:Number of max eats
}	t_data;

// PHILO
int			parse(t_data *data, int ac, char **av);
int			init(t_data *data);
void		*run(void *arg);

// UTILS
int			ft_atoi(char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isspace(char c);
int			ft_isdigit(int c);
int			ft_error(char *error, int retval);
void		*ft_calloc(size_t count, size_t size);

#endif
