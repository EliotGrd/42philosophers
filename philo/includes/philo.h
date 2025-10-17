/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:57:59 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/15 22:29:57 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define USAGE "\nUsage Philosophers :\n\n  ./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> (<number_of_time_each_philosopher_must_eat>)\n\n"

typedef struct s_philo
{
	struct s_global	*bla;
	int				ate;
}					t_philo;

typedef struct s_global
{
	int				philo_count;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				must_eat_count;
}					t_global;

int					parse_args(t_global *global, int argc, char **argv);

#endif
