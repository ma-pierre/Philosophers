/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:24:28 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/21 00:05:02 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	if (arg_is_digit(&av[1]))
		return (1);
	if (ft_atoll(av[1]) > 200 || ft_atoll(av[1]) < 1)
		return (printf("Number of philosophers must be from 1 to 200\n"), 1);
	i = 2;
	while (av[i])
	{
		if (arg_is_digit(&av[i]))
			return (1);
		if (ft_atoll(av[i]) > 2147483647 || ft_atoll(av[i]) < 0)
			return (printf("Arguments must be > 0 and <= to INT_MAX\n"), 1);
		i++;
	}
	if (ft_atoll(av[2]) < 60 || ft_atoll(av[3]) < 60 || ft_atoll(av[4]) < 60)
		return (printf("Time_to_*** must be at least 60ms\n"), 1);
	return (0);
}

int	philo_dining_alone(t_data *data)
{
	pthread_t	supervisor;

	if (pthread_create(&data->tid[0], NULL
			, &philo_is_alone, &data->philos[0]))
		return (1);
	ft_sleep(10);
	if (pthread_create(&supervisor, NULL, &supervisor_routine, data))
		return (1);
	pthread_join(data->tid[0], NULL);
	pthread_join(supervisor, NULL);
	return (0);
}

void	clear_data(t_data	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->full);
	pthread_mutex_destroy(&data->check_starvation);
	pthread_mutex_destroy(&data->init);
	clear_data(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (parsing(ac, av))
		return (0);
	i = init_all(ac, av, &data);
	if (i == 2)
		return (0);
	else if (i == 1)
	{
		clear_data(&data);
		return (0);
	}
	if (run_diner(&data))
	{
		printf(THREAD_ERROR);
		ft_exit(&data);
	}
	ft_exit(&data);
	return (0);
}
