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

void	init_philo(int argc, char *argv[], t_philo *philo)
{
	philo->idx = 0;
	philo->pnum = (ft_atoi(argv[1]));
	philo->ttdie = ft_atoi(argv[2]) * 1000;
	philo->tteat = ft_atoi(argv[3]) * 1000;
	philo->ttsleep = ft_atoi(argv[4]) * 1000;
	if (5 < argc)
		philo->eatnum = ft_atoi(argv[5]);
	philo->parr = malloc(sizeof(t_p) * philo->pnum);
	philo->death = 0;
}

void	init_mutex(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->pnum);
	i = 0;
	while (i < philo->pnum)
	{
		if (0 < pthread_mutex_init(&philo->forks[i], NULL))
			exit(-1);
		i++;
	}
	pthread_mutex_init(&philo->idx_lock, NULL);
	pthread_mutex_init(&philo->term, NULL);
	pthread_mutex_lock(&philo->term);
}

void	init_pthread(t_philo *philo)
{
	while (philo->idx < philo->pnum)
	{
		pthread_mutex_lock(&philo->idx_lock);
		if ((pthread_create(&philo->parr[philo->idx].t, NULL, (void*)thread_func, philo) < 0)\
		 || (pthread_create(&philo->parr[philo->idx].m, NULL, (void*)monitor, philo) < 0))
			exit (-1);
		usleep(10);
		philo->idx++;//ㅇㅕ기 확인
	}
}

void	init(int argc, char *argv[], t_philo *philo)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Err: invalid argument\n");
		exit(-1);
	}
	gettimeofday(&philo->start, NULL);
	
	init_philo(argc, argv, philo);
	init_mutex(philo);
	init_pthread(philo);
}
