/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:15:50 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/20 21:13:58 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_data *data)
{
	int	i;

	i = 1;
	pthread_mutex_init(&data->forks[0], NULL);
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
		{
			printf(MUTEX_ERROR);
			return (1);
		}
	}
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->nb_of_philo -1];
	if (data->nb_of_philo > 1)
	{
		i = 1;
		while (i < data->nb_of_philo)
		{
			data->philos[i].l_fork = &data->forks[i];
			data->philos[i].r_fork = &data->forks[i - 1];
			i++;
		}
	}
	return (0);
}

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->nb_of_philo);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->tid || !data->philos || !data->forks)
	{
		printf(ALLOC_ERROR);
		return (1);
	}
	return (0);
}

int	init_philos(t_data *data, int ac)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philos[i].starvation = 0;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (ac == 6)
			data->philos[i].meal_count = 0;
		else if (ac == 5)
			data->philos[i].meal_count = -2;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = (long int)ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_dead = 0;
	data->all_full = 0;
	if (ac == 6)
	{
		data->meal_nb = ft_atoi(av[5]);
		if (data->meal_nb == 0)
			return (printf("Meal number must be at least 1 or empty\n"), 1);
	}		
	if (ac == 5)
		data->meal_nb = -1;
	if (pthread_mutex_init(&data->full, NULL)
		|| pthread_mutex_init(&data->check_starvation, NULL)
		|| pthread_mutex_init(&data->print, NULL)
		|| pthread_mutex_init(&data->dead, NULL)
		|| pthread_mutex_init(&data->init, NULL))
	{
		printf(MUTEX_ERROR);
		return (1);
	}
	return (0);
}

int	init_all(int ac, char **av, t_data *data)
{
	if (init_data(data, ac, av))
		return (2);
	if (alloc(data))
		return (1);
	if (init_fork(data))
		return (1);
	if (init_philos(data, ac))
		return (1);
	return (0);
}
