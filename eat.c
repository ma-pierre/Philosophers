/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:20:55 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/21 00:04:18 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_infos(philo, "has taken a fork", 0);
		print_infos(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_infos(philo, "has taken a fork", 0);
		print_infos(philo, "has taken a fork", 0);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	*philo_is_alone(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->check_starvation);
	philo->starvation = philo->data->start_time + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->check_starvation);
	while (philo->meal_count < philo->data->meal_nb)
	{
		pthread_mutex_lock(philo->r_fork);
		print_infos(philo, "has taken a fork", 0);
		ft_sleep(philo->data->time_to_die);
		return (NULL);
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	print_infos(philo, "is eating", 0);
	pthread_mutex_lock(&philo->data->check_starvation);
	philo->starvation = get_ms_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->check_starvation);
	if (ft_usleep((useconds_t)philo->data->time_to_eat, philo->data))
		return (1);
	return (0);
}

void	print_infos(t_philo *philo, char *str, int dead)
{
	long int	time_ms;

	time_ms = get_ms_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->print);
	if (!dead && philo->data->is_dead == 0)
		printf("%lu %d %s\n", time_ms, philo->id, str);
	if (dead)
	{
		printf("%lu %d %s\n", time_ms, philo->id, str);
		philo->data->is_dead = 1;
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->dead);
}
