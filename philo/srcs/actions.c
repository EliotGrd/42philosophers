/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:42:45 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 19:39:42 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	pick_right_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->global->forks[philo->index]);
		print_status(philo, FORK_R); // pas sur de l'ordre parce que bizarre d'afficher qu'il prends une fourchette si c'est pour qu'il se passe des trucs avant de manger ??
		if (philo->index > 0)
		pthread_mutex_lock(&philo->global->forks[philo->index - 1]);
		else
			pthread_mutex_lock(&philo->global->forks[philo->global->philo_count]);
		print_status(philo, FORK_L);
	}
	else
	{
		if (philo->index > 0)
		pthread_mutex_unlock(&philo->global->forks[philo->index - 1]);
		else
			pthread_mutex_unlock(&philo->global->forks[philo->global->philo_count]);
		print_status(philo, FORK_L);
		pthread_mutex_unlock(&philo->global->forks[philo->index]);
		print_status(philo, FORK_R);	
	}
}

int	eating(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	pick_right_fork(philo);
	pthread_mutex_lock(&philo->last_meal_lock);
	usleep_check_death(philo->global->tteat, philo);
	philo->last_meal = timestamp();
	print_status(philo, EAT); // pas sur de l'ordre ici aussi
	philo->already_eat_count += 1;
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	print_status(philo, SLEEP);
	usleep_check_death(philo->global->ttsleep, philo);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	return (0);
	print_status(philo, THINK);
	if (philo->index % 2 == 0)
		return (0);
	//die >= 3 * eat + sleep
	
}
