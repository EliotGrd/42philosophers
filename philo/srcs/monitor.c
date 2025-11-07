/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:48:45 by egiraud           #+#    #+#             */
/*   Updated: 2025/11/07 14:27:15 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	flag_death(t_global *global, int i)
{
	unsigned int	time;

	time = timestamp();
	pthread_mutex_lock(&global->philos[i].last_meal_lock);
	if ((time - global->philos[i].last_meal) >= (unsigned int)global->ttdie)
	{
		pthread_mutex_unlock(&global->philos[i].last_meal_lock);
		pthread_mutex_lock(&global->stop_sim_lock);
		global->stop_sim = 1;
		pthread_mutex_unlock(&global->stop_sim_lock);
		print_status(&global->philos[i], DIED);
		return (1);
	}
	pthread_mutex_unlock(&global->philos[i].last_meal_lock);
	return (0);
}

int	monitor_routine_loop(t_global *global, int i, int all_philo_full)
{
	while (1)
	{
		i = 0;
		all_philo_full = 1;
		while (i < global->philo_count)
		{
			if (flag_death(global, i))
				return (1);
			pthread_mutex_lock(&global->philos[i].last_meal_lock);
			if (global->philos[i].already_eat_count < global->must_eat_count)
				all_philo_full = 0;
			pthread_mutex_unlock(&global->philos[i].last_meal_lock);
			i++;
		}
		if (all_philo_full == 1 && global->must_eat_count != -1)
		{
			pthread_mutex_lock(&global->stop_sim_lock);
			global->stop_sim = 1;
			pthread_mutex_unlock(&global->stop_sim_lock);
		}
		usleep(200);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_global	*global;
	int			all_philo_full;
	int			i;

	i = 0;
	all_philo_full = 0;
	global = (t_global *)arg;
	pthread_mutex_lock(&global->start_lock);
	pthread_mutex_unlock(&global->start_lock);
	if (monitor_routine_loop(global, i, all_philo_full))
		return (NULL);
	return (NULL);
}
