/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:42:03 by ybong             #+#    #+#             */
/*   Updated: 2021/10/25 16:42:03 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_forks(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->pnum);
	i = 0;
	while (i < philo->pnum)
	{
		if (0 <pthread_mutex_init(&philo->forks[i], NULL))
			exit(-1);
	}
}

void	init_philo(int argc, char *argv[], t_philo *philo)
{
	philo->idx = 0;
	philo->pnum = atoi(argv[1]);
	philo->ttdie = atoi(argv[2]) * 1000;
	philo->tteat = atoi(argv[3]) * 1000;
	philo->ttsleep = atoi(argv[4]) * 1000;
	if (5 < argc)
		philo->eatnum = atoi(argv[5]);
	philo->parr = malloc(sizeof(t_p) * philo->pnum);
	init_forks(philo);
}


void init_pthread(t_philo *philo, int n)
{//odd 1 even 0 
	int	i;

	i = 0;
	while (i < philo->pnum)
	{
		if (i % 2 == n)
		{
			if (pthread_create(pthread_t threada, NULL, function) < 0)
				return;//
		}
	}
}

void	init(int argc, char *argv[], t_philo *philo)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Err: invalid argument\n");
		exit(-1);
	}
	init_philo(argc, argv, philo);
}
