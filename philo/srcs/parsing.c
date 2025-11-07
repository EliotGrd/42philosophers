/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:25:18 by egiraud           #+#    #+#             */
/*   Updated: 2025/11/07 14:21:38 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	are_all_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= 48 && av[i][j] <= 57))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_atoi_safe_positive(const char *nptr)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!nptr[i])
		return (nb);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (((nb * 10) + (nptr[i] - '0')) > INT_MAX)
			return (-1);
		nb = (nb * 10) + (nptr[i++] - '0');
	}
	return (nb);
}

int	parse_args(t_global *gb, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n %s", USAGE), 1);
	if (are_all_digits(av))
		return (printf("Args given contains not only digits\n"), 1);
	gb->philo_count = ft_atoi_safe_positive(av[1]);
	gb->ttdie = ft_atoi_safe_positive(av[2]);
	gb->tteat = ft_atoi_safe_positive(av[3]);
	gb->ttsleep = ft_atoi_safe_positive(av[4]);
	if (av[5])
		gb->must_eat_count = ft_atoi_safe_positive(av[5]);
	else
		gb->must_eat_count = -1;
	if (gb->philo_count == -1 || gb->ttdie == -1 || gb->tteat == -1
		|| gb->ttsleep == -1 || gb->ttsleep == -1)
		return (printf("Number too big (int overflow) :(\n"), 1);
	if (gb->philo_count == 0 || gb->ttdie == 0 || gb->tteat == 0
		|| gb->ttsleep == 0 || gb->ttsleep == 0)
		return (printf("All numbers must be greater than 0\n"), 1);
	return (0);
}
