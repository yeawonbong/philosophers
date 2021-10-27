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

int		isargs_digit(int argc, char *argv[])
{
	int	i;
	int	j;

	if (!(argc == 5 || argc == 6))
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_philo(int argc, char *argv[], t_philo *philo)
{
	philo->idx = 0;
	
	if (isargs_digit(argc, argv) \
	|| (philo->pnum = ft_atoi(argv[1]) < 1) \
	|| (philo->ttdie = ft_atoi(argv[2]) * 1000 < 0) \
	|| (philo->tteat = ft_atoi(argv[3]) * 1000 < 0) \
	|| (philo->ttsleep = ft_atoi(argv[4]) * 1000 < 0))
	{
		printf("Err: invalid arguments\n");		
		return (1);
	}
	if (!philo->parr = malloc(sizeof(t_p) * philo->pnum))
		return (1);
	if (argc == 6)
		philo->eatnum = ft_atoi(argv[5]);
	else
		philo->eatnum = -1;
	philo->death = 0;
	return (0);
}

int	init_mutex(t_philo *philo) //fork, idx_lock, terminator
{
	int	i;

	if (!philo->forks = malloc(sizeof(pthread_mutex_t) * philo->pnum))
		return (1);
	i = 0;
	while (i < philo->pnum)
	{
		if (0 < pthread_mutex_init(&philo->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&philo->idx_lock, NULL);
	pthread_mutex_init(&philo->terminator, NULL);
	return (0);
}

int	init_pthread(t_philo *philo)
{
	if (pthread_create(&philo->main_t, NULL, (void*)terminator, philo) < 0)
		return (1);
	
	while (philo->idx < philo->pnum)
	{
		pthread_mutex_lock(&philo->idx_lock);
		if ((pthread_create(&philo->parr[philo->idx].t, NULL, (void*)thread_func, philo) < 0)\
		 || (pthread_create(&philo->parr[philo->idx].m, NULL, (void*)init_monitor, philo) < 0))
			return (1);
		usleep(10);
		philo->idx++;//ㅇㅕ기 확인
	}
}

int		init(int argc, char *argv[], t_philo *philo)
{
	int	i;

	i = 0;
	gettimeofday(&philo->start, NULL);
	if (init_philo(argc, argv, philo))
		return (1);
	if (init_mutex(philo))
		return (1);
	if (init_pthread(philo))
		return (1);
	while (i < philo->pnum)
		pthread_detach(philo->parr[i++].t);
	while (1)
	{
		if (!philo->pnum)
		{
			pthread_mutex_unlock(&philo->terminator);
		}
	//mutex free
	return (0);
}
