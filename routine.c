/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:06:39 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/21 00:56:53 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor_routine(void *data_ptr)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *)data_ptr;
	while (1)
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			philo = &data->philos[i];
			if (philos_full(data) == 1)
				return (NULL);
			if (supervisor_check_death(philo) == 1)
				return (NULL);
			i++;
		}
		ft_sleep(1);
	}
	return (NULL);
}

int	check_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->full);
	if (philo->data->all_full == philo->data->nb_of_philo)
	{
		pthread_mutex_unlock(&philo->data->full);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->full);
	return (0);
}

void	*philos_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->init);
	pthread_mutex_unlock(&philo->data->init);
	pthread_mutex_lock(&philo->data->check_starvation);
	philo->starvation = philo->data->start_time + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->check_starvation);
	if (!(philo->id % 2))
		ft_sleep((philo->data->nb_of_philo));
	while (1)
	{
		if (routine_check_death(philo->data) == 1)
			return (NULL);
		get_forks(philo);
		if (eat(philo))
			return (drop_forks(philo), NULL);
		if (routine_check_meal(philo) == 1)
			return (NULL);
		drop_forks(philo);
		sleep_think(philo);
		if (check_finish(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	run_diner(t_data *data)
{
	int			i;
	pthread_t	supervisor;

	i = -1;
	data->start_time = get_ms_time();
	if (data->nb_of_philo == 1)
		return (philo_dining_alone(data));
	pthread_mutex_lock(&data->init);
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &philos_routine,
				&data->philos[i]))
			return (1);
	}
	pthread_mutex_unlock(&data->init);
	ft_sleep(60);
	if (pthread_create(&supervisor, NULL, &supervisor_routine, data))
		return (1);
	i = -1;
	while (++i < data->nb_of_philo)
		pthread_join(data->tid[i], NULL);
	pthread_join(supervisor, NULL);
	return (0);
}

void	sleep_think(t_philo *philo)
{
	print_infos(philo, "is sleeping", 0);
	ft_usleep((useconds_t)philo->data->time_to_sleep, philo->data);
	print_infos(philo, "is thinking", 0);
	if (philo->data->time_to_eat + philo->data->time_to_sleep
		< philo->data->time_to_die)
		ft_usleep((philo->data->time_to_die - (philo->data->time_to_eat
					+ philo->data->time_to_sleep)) * 0.5, philo->data);
}
