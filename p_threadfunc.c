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

void	*eating(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->forks[id]);
	printf("%lldms Philosopher %2d has taken a fork on the right\n", get_timegap(philo->start), id);
	pthread_mutex_lock(&philo->forks[id + 1]);
	printf("%lldms Philosopher %2d has taken a fork on the left\n", get_timegap(philo->start), id);
	printf("%lldms Philosopher %2d is eating\n", get_timegap(philo->start), id);
	usleep(philo->tteat);
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[id + 1]);
	gettimeofday(&philo->parr[id].fin_eat, NULL); // 마지막으로 먹은 시점 p에 기록
	return (philo);
}

void	*sleeping(t_philo *philo, int id)
{
	printf("%lldms Philosopher %2d is sleeping\n", get_timegap(philo->start), id);
	usleep(philo->ttsleep);
	return (philo);
}

void	*thinking(t_philo *philo, int id)
{
	printf("%lldms Philosopher %2d is thinking\n", get_timegap(philo->start), id);
	return (philo);
}

void	*thread_func(t_philo *philo)
{
	int	id;
	if (philo->death)
		return(philo);
	id = philo->idx;
	gettimeofday(&philo->parr[id].fin_eat, NULL);
	printf("created_thread: philo %d\n", philo->idx);
	if (philo->idx % 2 == 1)
		usleep(100); // 처음에만 eating 늦게 시작
	while (1)
	{
		eating(philo, id);
		sleeping(philo, id);
		thinking(philo, id);
	}
	return (philo);
}