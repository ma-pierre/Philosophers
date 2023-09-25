/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:24:37 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/21 00:49:35 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(useconds_t time, t_data *data)
{
	u_int64_t	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < time)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		usleep(1);
	}
	return (0);
}

int	philos_full(t_data *data)
{
	if (data->meal_nb > 0)
	{
		pthread_mutex_lock(&data->full);
		if (data->all_full == data->nb_of_philo)
		{
			pthread_mutex_unlock(&data->full);
			return (1);
		}
		pthread_mutex_unlock(&data->full);
	}
	return (0);
}

int	supervisor_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_starvation);
	if (philo->starvation <= get_ms_time())
	{
		pthread_mutex_unlock(&philo->data->check_starvation);
		print_infos(philo, "died", 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_starvation);
	return (0);
}

int	routine_check_meal(t_philo *philo)
{
	if (philo->data->meal_nb > 0)
	{
		philo->meal_count += 1;
		if (philo->meal_count == philo->data->meal_nb)
		{
			pthread_mutex_lock(&philo->data->full);
			philo->data->all_full += 1;
			pthread_mutex_unlock(&philo->data->full);
			return (0);
		}
	}
	return (0);
}

int	routine_check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}
