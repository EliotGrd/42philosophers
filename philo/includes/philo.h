/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:57:59 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/19 20:36:39 by egiraud          ###   ########.fr       */
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

# define MALLOC "philo: Memory allocation failed\n"
# define MUTEX "philo: Mutex creation failed\n"
# define THREAD "philo: Thread creation failed\n"

typedef enum e_print
{
	EAT,
	SLEEP,
	THINK,
	FORK_R,
	FORK_L,
	DIED
}	t_print;

typedef struct s_philo
{
	int ate; // bool
	int				index;
	int				must_eat_count;
	int				already_eat_count;
	pthread_t		thread;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
	struct s_global	*global;
}					t_philo;

typedef struct s_global
{
	int				philo_count;
	t_philo			*philos;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				must_eat_count;
	int				stop_sim;
	pthread_t		monitor;
	pthread_mutex_t	lock_print;
	pthread_mutex_t stop_sim_lock;
	pthread_mutex_t	*forks;
}					t_global;

int					parse_args(t_global *global, int argc, char **argv);
void				start_philosophing(t_global *global);

unsigned int		timestamp(void);
void				ft_usleep(unsigned int ms);
void				ft_free(void **ptr);
void				stderr_msg(char *str);

#endif
