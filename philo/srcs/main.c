/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:59:53 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 20:45:44 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destructor(t_global *global, int to_free)
{
	int	i;

	i = 0;
	while (i < to_free)
	{
		pthread_mutex_destroy(&global->forks[i]);
		// pthread_mutex_destroy(&global->philos[i].fork_right);
		// pthread_mutex_destroy(&global->philos[i].fork_left);
		pthread_mutex_destroy(&global->philos[i].last_meal_lock);
		i++;
	}
	pthread_mutex_destroy(&global->start_lock);
	pthread_mutex_destroy(&global->lock_print);
	pthread_mutex_destroy(&global->stop_sim_lock);
	ft_free((void **)&global->philos);
	ft_free((void **)&global->forks);
}

int	init_philosophers(t_global *global)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * global->philo_count);
	if (!philos)
		return (destructor(global, 0), stderr_msg(MALLOC), 1);
	global->forks = malloc(sizeof(pthread_mutex_t) * global->philo_count);
	if (!global->forks)
		return (destructor(global, 0), stderr_msg(MALLOC), 1);
	i = 0;
	while (i < global->philo_count)
	{
		philos[i].index = i;
		philos[i].must_eat_count = global->must_eat_count; // pas necessaire ?
		philos[i].already_eat_count = 0;
		if (pthread_mutex_init(&global->forks[i], NULL))
			return (destructor(global, i - 1), 1);
		if (pthread_mutex_init(&philos[i].last_meal_lock, NULL))
			return (destructor(global, i - 1), pthread_mutex_destroy(&global->forks[i]), 1);
		philos[i].global = global;
		i++;
	}
	global->philos = philos;
	return (0);
}

int	init_global(t_global *global)
{
	if (pthread_mutex_init(&global->lock_print, NULL))
		return (1);
	if (pthread_mutex_init(&global->start_lock, NULL))
		return (pthread_mutex_destroy(&global->lock_print), 1);
	if (pthread_mutex_init(&global->stop_sim_lock, NULL))
		return (pthread_mutex_destroy(&global->lock_print),
			pthread_mutex_destroy(&global->start_lock), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_global	global;

	//global = malloc(sizeof(t_global));
	memset(&global, 0, sizeof(t_global));
	if (parse_args(&global, ac, av))
		return (-1);
	if (init_global(&global))
		return (-1);
	if (init_philosophers(&global))
		return (-1);
	start_philosophing(&global);
	destructor(&global, global.philo_count);
}
