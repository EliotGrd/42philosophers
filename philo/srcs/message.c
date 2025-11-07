/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:28:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/11/07 14:20:27 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	actual_print(t_philo *philo, char *str)
{
	printf("%d %d %s\n", (timestamp() - philo->global->start_time), philo->index
		+ 1, str);
}

/*static void	actual_print_debug(t_philo *philo, char *str)
{
	printf("%d %d %s [%d]\n", (timestamp() - philo->global->start_time),
		philo->index,
		str, philo->already_eat_count + 1);
}

void	print_status_debug(t_philo *philo, t_print type)
{
	pthread_mutex_lock(&philo->global->lock_print);
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
	pthread_mutex_unlock(&philo->global->lock_print);
}*/
void	print_status(t_philo *philo, t_print type)
{
	pthread_mutex_lock(&philo->global->lock_print);
	if (!check_death(philo))
	{
		if (type == FORK_R || type == FORK_L)
			actual_print(philo, "has taken a fork");
		else if (type == EAT)
			actual_print(philo, "is eating");
		else if (type == SLEEP)
			actual_print(philo, "is sleeping");
		else if (type == THINK)
			actual_print(philo, "is thinking");
	}
	if (type == DIED)
		actual_print(philo, "died");
	pthread_mutex_unlock(&philo->global->lock_print);
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
