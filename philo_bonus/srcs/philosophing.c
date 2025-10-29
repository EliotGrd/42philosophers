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
#include <stdlib.h>

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->global->start_lock);
	pthread_mutex_unlock(&philo->global->start_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (philo->index % 2 == 0)
		usleep(200); // voir comment ca se comporte tel quel
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

static void	*lone_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->global->forks);
	print_status(philo, FORK_R);
	sem_post(philo->global->forks);
	print_status(philo, DIED);
	return (NULL);
}

void	start_philosophing(t_global *global)
{
	int	i;

	i = 0;
	global->start_time = timestamp();
	if (global->philo_count == 1)
	{

		return ;
	}
	pthread_mutex_lock(&global->start_lock);
	if (pthread_create(&global->monitor, NULL, &monitor_routine, global))
		return (stderr_msg(THREAD));
	while (i < global->philo_count)
	{
		if (pthread_create(&global->philos[i].thread, NULL, &philo_routine,
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
	for (i = 0; i < global->philo_count; i++)
	{
		global->philos[i].last_meal = timestamp();
	}
	pthread_mutex_unlock(&global->start_lock);
	while (--i >= 0)
	{
		pthread_join(global->philos[i].thread, NULL);
	}
	pthread_join(global->monitor, NULL);
}

void	start_philosophing(t_global *global)
{
	int i;

	global->pids = malloc(sizeof(pid_t) * global->nb_philos);
	if (!global->pids)
		return -1;

	global->start_time = timestamp();


	while (i < global->nb_philos)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			stderr_msg(FORK);
			return -1;
		}
		if (pid == 0)
		{
			philo_routine(global, i);
			//je sais pas quoi faire la return ? 
		}
		else
		{
			global->pids[i] = pid;
		}
	}
	return 0;
}
