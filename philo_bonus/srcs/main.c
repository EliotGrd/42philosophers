/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:59:53 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 20:45:44 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static sem_t *open_clean_sem(const char *name, unsigned int value)
{
	sem_unlink(name);
	sem_t *s = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (s == SEM_FAILED)
	{
		stderr_msg(SEM);
		return NULL;
	}
	return s;
}

static int init_global(t_global *global)
{
	global->forks = open_clean_sem("forks_sem", global->philo_count);
	if (!global->forks)
		return -1;
	global->print_sem = open_clean_sem("print_sem", 1);
	if (!global->print_sem)
		return -1;
	global->stop_sim_sem = open_clean_sem("stop_sim_sem", 1);
	if (!global->stop_sim_sem)
		return -1;
	global->start_sem = open_clean_sem("start_sem", 0);
	if (!global->start_sem)
		return -1;


	return 0;
}

static void sem_destructor(void)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("stop_sim_sem");
	sem_unlink("start_sem");
}

void	destructor(t_global *global, int to_free)
{
	int	i;

	i = 0;
	while (i < to_free)
	{
		i++;
	}
	sem_destructor();
	ft_free((void **)&global->philos);
	ft_free((void **)&global->forks);
}

int	init_philosophers(t_global *global)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * global->philo_count);
	if (!philos)
		return (destructor(global, 0), stderr_msg(MALLOC), 1);
	i = 0;
	while (i < global->philo_count)
	{
		philos[i].index = i;
		philos[i].already_eat_count = 0;
		philos[i].global = global;
		i++;
	}
	global->philos = philos;
	return (0);
}

int	main(int ac, char **av)
{
	t_global	global;

	//global = malloc(sizeof(t_global));
	memset(&global, 0, sizeof(t_global));
	if (parse_args(&global, ac, av))
		return (-1);
	if (init_global(&global))
		return (-1);
	if (init_philosophers(&global))
		return (-1);
	start_philosophing(&global);
	destructor(&global, global.philo_count);
}
