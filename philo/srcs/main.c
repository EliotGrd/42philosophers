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
#include <pthread.h>

void	destructor(t_global *global)
{
	int i;

	i = 0;
	while (i < global->philo_count)
	{
		pthread_mutex_destroy(global->philos[i].&fork_right);
		pthread_mutex_destroy(global->philos[i].&fork_left);
		i++;
	}
	ft_free((void **)&global->philos);
}

void	init_philosophers(t_global *global)
{
	t_philo *philos;
	int i;

	philos = malloc(sizeof(t_philo) * global->philo_count);
	i = 0;
	while (i < global->philo_count)
	{
		philos[i].ate = 0;
		philos[i].already_eat_count = 0;
		philos[i].must_eat_count = global->must_eat_count;
		philos[i].index = i;
		//gerer les forks
		philos[i].global = global;
	}
	global->philos = philos;

}

void	init_global(t_global *global)
{
	memset(global, 0, sizeof(t_global));
	init_philosophers(global);
}


int main(int ac, char **av)
{
	t_global global;

	init_global(&global);
	if (parse_args(&global, ac, av))
		return (0);
	start_philosophing(&global);
	destructor(&global);
}

//typedef struct s_ctr
//{
//	pthread_mutex_t c_mutex;
//	int count;
//} t_ctr;
//
//void	init_global(t_global *global)
//{
//	memset(global, 0, sizeof(t_global));
//}
//
//void	*routine_test(void *arg)
//{
//	t_ctr *ctr = arg;
//
//	pthread_mutex_lock(&ctr->c_mutex);
//	printf("Init count : %d\n", ctr->count);
//	pthread_mutex_unlock(&ctr->c_mutex);
//	int i = 0;
//	while (i < 100000)
//	{
//		pthread_mutex_lock(&ctr->c_mutex);
//		ctr->count++;
//		pthread_mutex_unlock(&ctr->c_mutex);
//		i++;
//	}
//	pthread_mutex_lock(&ctr->c_mutex);
//	printf("Final count : %d\n", ctr->count);
//	pthread_mutex_unlock(&ctr->c_mutex);
//	return (arg);
//}
//
///**
// * @brief 
// *
// * @param argc 
// * @param argv 
// * @return 
// */
//int main(int argc, char **argv)
//{
//	t_global global;
//	pthread_t thread0;
//	pthread_t thread1;
//	t_ctr ctr;
//
//	init_global(&global);
//	if (parse_args(&global, argc, argv))
//		return (0);
//
//	ctr.count = 5;
//	pthread_mutex_init(&ctr.c_mutex, NULL);
//
//	pthread_create(&thread0, NULL, routine_test, &ctr);
//	printf("Thread %ld created\n", thread0);
//	
//	pthread_create(&thread1, NULL, routine_test, &ctr);
//	printf("Thread %ld created\n", thread1);
//
//	pthread_join(thread0, NULL);
//	printf("Thread %ld joined\n", thread0);
//	pthread_join(thread1, NULL);
//	printf("Thread %ld joined\n", thread1);
//	
//	pthread_mutex_destroy(&ctr.c_mutex);
//
//	printf("Global : %d\n", ctr.count);
//}
