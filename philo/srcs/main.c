/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:59:53 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/15 22:48:57 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_global(t_global *global)
{
	memset(global, 0, sizeof(t_global));
}

void	*routine_test(void *arg)
{
	printf("Threaded\n");
	return (arg);
}

/**
 * @brief 
 *
 * @param argc 
 * @param argv 
 * @return 
 */
int main(int argc, char **argv)
{
	t_global global;
	pthread_t thread;

	init_global(&global);
	if (parse_args(&global, argc, argv))
		return (0);
	pthread_create(&thread, NULL, routine_test, NULL);
}
