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

static void	actual_print(int index, char *str)
{
	printf("%du %d %s", timestamp(), index, str);
}

void	print_status(t_philo *philo, t_print type)
{
	//gerer le cas de mort differemment ?
	pthread_mutex_lock(&philo->global->lock_print);
	if (type == FORK_R || type == FORK_L)
		actual_print(philo->index, "has taken a fork");
	if (type == EAT)
		actual_print(philo->index, "is eating");
	if (type == SLEEP)
		actual_print(philo->index, "is sleeping");
	if (type == THINK)
		actual_print(philo->index, "is thinking");
	if (type == DIED)
		actual_print(philo->index, "died");
	pthread_mutex_unlock(&philo->global->lock_print);
}

void	stderr_msg(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}
