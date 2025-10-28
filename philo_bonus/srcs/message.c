/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:28:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/19 20:09:48 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	actual_print(t_philo *philo, char *str)
{
	sem_wait(philo->global->print_sem);
	printf("%d %d %s\n", (timestamp() - philo->global->start_time), philo->index,
		str);
	sem_post(philo->global->print_sem);
}

static void	actual_print_debug(t_philo *philo, char *str)
{
	sem_wait(philo->global->print_sem);
	printf("%d %d %s [%d]\n", (timestamp() - philo->global->start_time), philo->index,
		str, philo->already_eat_count + 1);
	sem_post(philo->global->print_sem);
}

void	print_status_debug(t_philo *philo, t_print type)
{
	if (type == FORK_R)
		actual_print_debug(philo, "has taken right fork");
	else if (type == FORK_L)
		actual_print_debug(philo, "has taken left fork");
	else if (type == LEAVE_R)
		actual_print_debug(philo, "has droped right fork");
	else if (type == LEAVE_L)
		actual_print_debug(philo, "has droped left fork");
	else if (type == EAT)
		actual_print_debug(philo, "is eating");
	else if (type == SLEEP)
		actual_print_debug(philo, "is sleeping");
	else if (type == THINK)
		actual_print_debug(philo, "is thinking");
	else if (type == DIED)
		actual_print_debug(philo, "died");
}

void	print_status(t_philo *philo, t_print type)
{
	if (type == FORK_R || type == FORK_L)
		actual_print(philo, "has taken a fork");
	else if (type == EAT)
		actual_print(philo, "is eating");
	else if (type == SLEEP)
		actual_print(philo, "is sleeping");
	else if (type == THINK)
		actual_print(philo, "is thinking");
	else if (type == DIED)
		actual_print(philo, "died");
}

void	stderr_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}
