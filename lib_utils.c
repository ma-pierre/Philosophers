/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:24:47 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/20 05:41:29 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoll(const char *str)
{
	long int	i;
	long int	res;
	int			mp;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	mp = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mp *= -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - 48));
		i++;
	}
	return (res * mp);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	mp;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	mp = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mp *= -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - 48));
		i++;
	}
	return (res * mp);
}

int	arg_is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				printf("Only numeric characters are accepted as valid inputs\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

long int	get_ms_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (long int)1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(unsigned long time)
{
	u_int64_t	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < time)
	{
		usleep(120);
	}
	return ;
}
