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

void	*monitor_routine(void *arg)
{
	t_global *global;
	int i;

	i = 0;
	global = (t_global *)arg;
	while (1)
	{
		while (i < global->philo_count)
		{
			pthread_mutex_lock(&global->philos[i].last_meal_lock);
			if (global->philos[i].last_meal > global->ttdie)
			{
				pthread_mutex_lock(&global->stop_sim_lock);
				global->stop_sim = 1;
				pthread_mutex_unlock(&global->stop_sim_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&global->philos[i].last_meal_lock);
			i++;
		}
		//usleep leger pour pas niquer le cpu ?
		usleep(1000);
	}
	return (NULL);
}
