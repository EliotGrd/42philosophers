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
	sem_wait(global->philos[i].last_meal_sem);
	if ((time - global->philos[i].last_meal) >= (unsigned int)global->ttdie)
	{
		sem_post(global->philos->last_meal_sem);
		sem_wait(global->stop_sim_sem);
		global->stop_sim = 1;
		sem_post(global->stop_sim_sem);
		return (1);
	}
	sem_post(global->philos->last_meal_sem);
	return (0);
}

void	philo_death_monitor(t_philo *philo)
{
	while (1)
	{
		if (philo->already_eat_count >= philo->global->must_eat_count)
			return ;//verif que c le cas pour tous ? ou verif ca seulement dans le process parent ?
		if (flag_death(philo->global, philo->index))
			return ;
	}
}

//wait till le sem all philo ate est du nombre de philo ca veut dire ils ont tous mange
//
//wait pid sur le tableau de pid pour exit propre

//void	*monitor_routine(void *arg)
//{
//	t_global *global;
//	int	all_philo_full;
//	int i;
//
//	global = (t_global *)arg;
//	while (1)
//	{
//		i = 0;
//		all_philo_full = 1;
//		while (i < global->philo_count)
//		{
//			if (flag_death(global, i))
//				return (NULL);
//			sem_wait(global->philos[i].last_meal_sem);
//			if (global->philos[i].already_eat_count < global->must_eat_count)
//				all_philo_full = 0;
//			sem_post(global->philos[i].last_meal_sem);
//			i++;
//		}
//		if (all_philo_full == 1 && global->must_eat_count != -1)
//		{
//			sem_wait(global->stop_sim_sem);
//			global->stop_sim = 1;
//			sem_post(global->stop_sim_sem);
//		}
//		usleep(100); //fine tune 200 test a faire
//	}
//	return (NULL);
//}

void	monitor_routine(t_global *global)
{
	sem_wait(global->stop_sim_sem);
	//kill loop on pids
	//waitpid
	destr
	exit();
}

//demander pour etre sur de quoi faire dans le cas ou tout le monde a assez mange

//pour l'instant max meals fonctionne que sur les impairs
//comment faire pour que seulement un philo die
