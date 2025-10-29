/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:57:59 by egiraud           #+#    #+#             */
/*   Updated: 2025/10/20 20:15:46 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
#include <sched.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define USAGE "\nUsage Philosophers :\n\n  ./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> (<number_of_time_each_philosopher_must_eat>)\n\n"

# define MALLOC "philo: Memory allocation failed\n"
# define MUTEX "philo: Mutex creation failed\n"
# define THREAD "philo: Thread creation failed\n"
# define SEM "philo: Semaphore creation failed\n"
# define FORK "philo: Fork failed\n"

typedef enum e_print
{
	EAT,
	SLEEP,
	THINK,
	FORK_R,
	LEAVE_R,
	FORK_L,
	LEAVE_L,
	DIED
}					t_print;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int must_eat_count; // pas necessaire ?
	int				already_eat_count;
	unsigned int	last_meal;
	sem_t			*last_meal_sem;
	sem_t			*fork_sem;
	unsigned int	forks_held;
	struct s_global	*global;
}					t_philo;

typedef struct s_global
{
	int				philo_count;
	t_philo			*philos;
	pid_t			*pids;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				must_eat_count;
	int				stop_sim;
	unsigned int	start_time;
	pthread_t		monitor;
	sem_t			*start_sem;
	sem_t			*print_sem;
	sem_t			*stop_sim_sem;
	sem_t			*forks;
}					t_global;

int					parse_args(t_global *global, int argc, char **argv);
int				start_philosophing(t_global *global);
void				*monitor_routine(void *arg);

int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);
void				print_status(t_philo *philo, t_print type);

void				print_status_debug(t_philo *philo, t_print type);

int					check_death(t_philo *philo);
unsigned int		timestamp(void);
int					usleep_check_death(unsigned int ms, t_philo *philo);
void				ft_free(void **ptr);
void				stderr_msg(char *str);

#endif
