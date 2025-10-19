/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 23:00:39 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/19 20:37:34 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->stop_sim_lock);
	if (philo->global->stop_sim == 1)
		return (pthread_mutex_unlock(&philo->global->stop_sim_lock), 1);
	pthread_mutex_unlock(&philo->global->stop_sim_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		//check_death puis break;
	}
}

void	start_philosophing(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->philo_count)
	{
		pthread_create(&global->philos[i].thread, NULL, philo_routine, &global->philos[i]);
		i++;
	}
	// lancer le thread moniteur ?
	i = 0;
	while (i < global->philo_count)
	{
		pthread_join(global->philos[i].thread, NULL);
		i++;
	}
}
