/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:13:25 by mapierre          #+#    #+#             */
/*   Updated: 2023/09/21 00:04:07 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define ALLOC_ERROR "MEMORY ALLOCATION ERROR\n"
# define MUTEX_ERROR "INIT MUTEX FAILED\n"
# define THREAD_ERROR "INIT / JOIN THREAD ERROR\n"

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	long int		starvation;
	int				meal_count;
	int				lf_lock;
	int				rf_lock;
	int				full;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	pthread_t		*t_supervisor;
	t_philo			*philos;
	int				nb_of_philo;
	int				time_to_eat;
	long int		time_to_die;
	int				time_to_sleep;
	int				is_dead;
	int				all_full;
	int				meal_nb;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	init;
	pthread_mutex_t	full;
	pthread_mutex_t	dead;
	pthread_mutex_t	sleep;
	pthread_mutex_t	check_starvation;
}	t_data;

long int	ft_atoll(const char *str);
int			ft_atoi(const char *str);
int			init_all(int ac, char **av, t_data *data);
int			init_data(t_data *data, int ac, char **av);
int			init_fork(t_data *data);
int			init_philos(t_data *data, int ac);
int			ft_usleep(useconds_t time, t_data *data);
int			alloc(t_data *data);
long int	get_ms_time(void);
void		print_infos(t_philo *philo, char *str, int dead);
void		get_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
int			run_diner(t_data *data);
void		ft_exit(t_data *data);
void		clear_data(t_data *data);
int			arg_is_digit(char **av);
void		*supervisor_routine(void *data_ptr);
void		*philo_is_alone(void *philo_ptr);
int			philos_full(t_data *data);
int			routine_check_meal(t_philo *philo);
int			supervisor_check_death(t_philo *philo);
int			routine_check_death(t_data *data);
void		ft_sleep(unsigned long time);
int			philo_dining_alone(t_data *data);
int			eat(t_philo *philo);
void		sleep_think(t_philo *philo);
#endif
