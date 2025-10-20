/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 23:00:39 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 20:16:01 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->global->start_lock);
	pthread_mutex_unlock(&philo->global->start_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = timestamp();
	pthread_mutex_lock(&philo->last_meal_lock);
	if (philo->index % 2 == 0)
		usleep(100); // voir comment ca se comporte tel quel
	//
	while (1)
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

void	*lone_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->global->forks[0]);
	print_status(philo, FORK_R);
	pthread_mutex_unlock(&philo->global->forks[0]);
	print_status(philo, DIED);
	return (NULL);
}

void	start_philosophing(t_global *global)
{
	int	i;

	i = 0;
	if (global->philo_count == 1)
	{
		pthread_create(&global->philos[0].thread, NULL, lone_philo_routine,
			&global->philos[0]);
		pthread_join(global->philos[0].thread, NULL);
		return ;
	}
	// thread moniteur
	if (pthread_create(&global->monitor, NULL, monitor_routine, global))
		return (stderr_msg(THREAD));
	pthread_mutex_lock(&global->start_lock);
	while (i < global->philo_count)
	{
		if (pthread_create(&global->philos[i].thread, NULL, philo_routine,
				&global->philos[i]))
		{
			pthread_mutex_lock(&global->stop_sim_lock);
			global->stop_sim = 1;
			pthread_mutex_unlock(&global->stop_sim_lock);
			stderr_msg(THREAD);
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&global->start_lock);
	while (i > 0)
	{
		pthread_join(global->philos[i].thread, NULL);
		i--;
	}
}
