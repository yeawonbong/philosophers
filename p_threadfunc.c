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

int		eating(t_philo *philo, int id)
{
	if (philo->death)
		return (1);
	pthread_mutex_lock(&philo->forks[id]);
	printf("%5lldms Philosopher%2d has taken a fork on the right\n", get_timegap(philo->start), id);
	pthread_mutex_lock(&philo->forks[id + 1]);
	printf("%5lldms Philosopher%2d has taken a fork on the left\n", get_timegap(philo->start), id);
	philo->parr[id].status = EAT;
	printf("%5lldms Philosopher%2d is eating\n", get_timegap(philo->start), id);
	usleep(philo->tteat);
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[id + 1]);
	gettimeofday(&philo->parr[id].fin_eat, NULL); // 마지막으로 먹은 시점 p에 기록
	return (0);
}

int		sleeping(t_philo *philo, int id)
{
	if (philo->death)
		return (1);
	philo->parr[id].status = SLEEP;
	printf("%5lldms Philosopher%2d is sleeping\n", get_timegap(philo->start), id);
	usleep(philo->ttsleep);
	return (0);
}

int		thinking(t_philo *philo, int id)
{
	if (philo->death)
		return (1);
	philo->parr[id].status = THINK;
	printf("%5lldms Philosopher%2d is thinking\n", get_timegap(philo->start), id);
	return (0);
}

void	*thread_func(t_philo *philo)
{
	int	id;
	if (philo->death)
		return(0);
	id = philo->idx;
printf("====쓰레드 %d 만들었다 함수 시작!!\n", id);
	pthread_mutex_unlock(&philo->idx_lock);
	gettimeofday(&philo->parr[id].fin_eat, NULL);
	printf("created_thread: philo %d\n", philo->idx);
	if (id % 2 == 1)
		usleep(100); // 처음에만 eating 늦게 시작
printf("MID_thread_func!!\n");
	while (1)
	{
		if (philo->death)
			break;
		if (eating(philo, id))
			break;
		if (sleeping(philo, id))
			break;
		if (thinking(philo, id))
			break;
	}
	printf("죽는다죽어 id: %d\n", id);
	return (0);
}