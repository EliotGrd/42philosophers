/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:35:48 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 15:55:00 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	sem_wait(philo->global->stop_sim_sem);
	if (philo->global->stop_sim == 1)
		return (sem_post(philo->global->stop_sim_sem), 1);
	sem_post(philo->global->stop_sim_sem);
	return (0);
}

unsigned int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	usleep_check_death(unsigned int ms, t_philo *philo)
{
	unsigned int	wake_up;

	wake_up = timestamp() + ms;
	while (timestamp() <= wake_up)
	{
		usleep(100);
		if (check_death(philo))
			return (1);
	}
	return (0);
}

void    ft_free(void **ptr)
{
        if (!*ptr || !ptr)
                return ;
        free(*ptr);
        *ptr = NULL;
}
