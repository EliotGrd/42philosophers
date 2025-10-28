/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:48:45 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 20:15:27 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	flag_death(t_global *global, int i)
{
	unsigned int time;

	time = timestamp();
	pthread_mutex_lock(&global->philos[i].last_meal_lock);
	if ((time - global->philos[i].last_meal) >= (unsigned int)global->ttdie)
	{
		pthread_mutex_unlock(&global->philos[i].last_meal_lock);
		pthread_mutex_lock(&global->stop_sim_lock);
		global->stop_sim = 1;
		pthread_mutex_unlock(&global->stop_sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&global->philos[i].last_meal_lock);
	return (0);
}

//wait till le sem all philo ate est du nombre de philo ca veut dire ils ont tous mange
//
//wait pid sur le tableau de pid pour exit propre

void	*monitor_routine(void *arg)
{
	t_global *global;
	int	all_philo_full;
	int i;

	global = (t_global *)arg;
	pthread_mutex_lock(&global->start_lock);
	pthread_mutex_unlock(&global->start_lock);
	while (1)
	{
		i = 0;
		all_philo_full = 1;
		while (i < global->philo_count)
		{
			if (flag_death(global, i))
				return (NULL);
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
		usleep(100); //fine tune 200 test a faire
	}
	return (NULL);
}

//demander pour etre sur de quoi faire dans le cas ou tout le monde a assez mange

//pour l'instant max meals fonctionne que sur les impairs
//comment faire pour que seulement un philo die
