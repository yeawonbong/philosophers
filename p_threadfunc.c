/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_threadfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:33:15 by ybong             #+#    #+#             */
/*   Updated: 2021/10/25 19:33:15 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating(t_philo *philo)
{
	int idx;

	idx = philo->idx;
	pthread_mutex_lock(&philo->forks[idx]);
	printf("%dms Philosopher %2d has taken a fork\n");	
	pthread_mutex_lock(&philo->forks[idx + 1]);
	printf("%dms Philosopher %2d has taken a fork\n");
	printf("%dms Philosopher %2d is eating\n");
	usleep(philo->tteat);
	pthread_mutex_unlock(&philo->forks[idx]);
	pthread_mutex_unlock(&philo->forks[idx + 1]);
	gettimeofday(&philo->parr[idx].fin_eat, NULL); // 마지막으로 먹은 시점 p에 기록
}

void	*sleeping(t_philo *philo)
{

}

void	*thinking(t_philo *philo)
{

}

void	*thread_func(t_philo *philo)
{
	if (philo->idx % 2 == 1)
		usleep(100); // 처음에만 eating 늦게 시작
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}