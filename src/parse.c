/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:05:53 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 17:20:42 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumber(const char *s)
{
	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	while (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	parse(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (!ft_isnumber(av[i]))
			return (0);
	ft_bzero(data, sizeof(t_data));
	data->args[4] = -1;
	i = -1;
	while (++i < ac)
	{
		data->args[i] = ft_atoi(av[i + 1]);
		if (data->args[i] < 0)
			return (0);
	}
	return (1);
}
