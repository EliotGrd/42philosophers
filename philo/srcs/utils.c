/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:35:48 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/19 20:37:36 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned int ms)
{
	unsigned int	wake_up;

	wake_up = timestamp() + ms;
	while (timestamp() < wake_up)
	{
		//if simu ended break;
		usleep(100);
	}
}

void    ft_free(void **ptr)
{
        if (!*ptr || !ptr)
                return ;
        free(*ptr);
        *ptr = NULL;
}
