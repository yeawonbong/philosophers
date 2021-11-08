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
	|| ((philo->in.pnum = ft_atoi(argv[1])) < 1) \
	|| ((philo->in.ttdie = ft_atoi(argv[2])) < 0) \
	|| ((philo->in.tteat = ft_atoi(argv[3])) < 0) \
	|| ((philo->in.ttsleep = ft_atoi(argv[4])) < 0))
	{
		printf("Err: invalid arguments\n");		
		return (1);
	}
	printf("- pnum: %d\n- ttdie: %lld\n- tteat: %lld\n- ttsleep: %lld\n", philo->in.pnum, philo->in.ttdie, philo->in.tteat, philo->in.ttsleep);
	if (!(philo->parr = malloc(sizeof(t_p) * philo->in.pnum)))
		return (1);
	if (argc == 6)
		philo->in.eatnum = ft_atoi(argv[5]);
	else
		philo->in.eatnum = -1;
	philo->death = 0;
	philo->ate_all = 0;
	return (0);
}

int	init_mutex(t_philo *philo) //fork, idx_lock, terminator
{
	int	i;

	if (!(philo->forks = malloc(sizeof(pthread_mutex_t) * philo->in.pnum)))
		return (1);
	i = 0;
	while (i < philo->in.pnum)
	{
		if (0 < pthread_mutex_init(&philo->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&philo->term, NULL);
	pthread_mutex_init(&philo->m_lock, NULL);
	pthread_mutex_init(&philo->death_lock, NULL);
	pthread_mutex_init(&philo->print_lock, NULL);
	pthread_mutex_lock(&philo->term);
	pthread_mutex_lock(&philo->m_lock);
	return (0);
}

int	init_pthread(t_philo *philo)
{
	while (philo->idx < philo->in.pnum)
	{
		if ((pthread_create(&philo->parr[philo->idx].t, NULL, (void*)thread_func, philo) != 0)\
		 || (pthread_create(&philo->parr[philo->idx].m, NULL, (void*)monitor, philo) != 0))
			return (1);
		pthread_mutex_init(&philo->parr[philo->idx].eating, NULL);
		usleep(100);
		philo->idx++;//ㅇㅕ기 확인
	}
	pthread_mutex_unlock(&philo->m_lock);
	return (0);
}

int		init(int argc, char *argv[], t_philo *philo)
{
	int	i;
printf("init!\n");
	i = 0;
	gettimeofday(&philo->start, NULL);
	if (init_philo(argc, argv, philo))
		return (1);
	if (init_mutex(philo))
		return (1);
	if (init_pthread(philo))
		return (1);
	return (0);
}
