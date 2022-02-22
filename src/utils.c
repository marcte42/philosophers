/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:05:53 by mterkhoyev        #+#    #+#             */
/*   Updated: 2022/02/11 16:31:43 by mterkhoyev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_ms(void)
{
	t_time	curr;

	gettimeofday(&curr, NULL);
	return (curr.tv_sec * 1000 + curr.tv_usec / 1000);
}

unsigned long	time_ms(unsigned long start)
{
	return (get_ms() - start);
}

int	elapsed_time_since(t_time time)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	curr_time.tv_sec = curr_time.tv_sec - time.tv_sec;
	curr_time.tv_usec = curr_time.tv_usec - time.tv_usec;
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = dest;
	while (len--)
		*ptr++ = c;
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, size * count);
	return (tmp);
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	sign = 1;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_error(char *error, int retval)
{
	printf("%s", error);
	return (retval);
}
