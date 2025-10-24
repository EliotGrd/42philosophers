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

static void	lock_right_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->global->forks[philo->index]);
		print_status_debug(philo, FORK_R);
		pthread_mutex_lock(&philo->global->forks[philo->index - 1 % philo->global->philo_count]);
		print_status_debug(philo, FORK_L);
	}
	else
	{
		pthread_mutex_lock(&philo->global->forks[philo->index - 1 % philo->global->philo_count]);
		print_status_debug(philo, FORK_L);
		pthread_mutex_lock(&philo->global->forks[philo->index]);
		print_status_debug(philo, FORK_R);
	}
}

static void unlock_right_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->index]);
		print_status_debug(philo, LEAVE_R);
		pthread_mutex_unlock(&philo->global->forks[philo->index - 1 % philo->global->philo_count]);
		print_status_debug(philo, LEAVE_L);
	}
	else
	{
		pthread_mutex_unlock(&philo->global->forks[philo->index - 1 % philo->global->philo_count]);
		print_status_debug(philo, LEAVE_L);
		pthread_mutex_unlock(&philo->global->forks[philo->index]);
		print_status_debug(philo, LEAVE_R);
	}

}

int	eating(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	lock_right_fork(philo);
	print_status_debug(philo, EAT); // pas sur de l'ordre ici aussi
	usleep_check_death(philo->global->tteat, philo);
	unlock_right_fork(philo);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = timestamp();
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
