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

static int	grab_fork(t_philo *philo, int id, char c)
{
	if (c == RIGHT)
	{
		pthread_mutex_lock(&philo->forks[id]);
		if (death_detector(philo))
			return (1);
		print_status(philo, id, "has taken a fork on the right");
	}
	else if (c == LEFT)
	{
		pthread_mutex_lock(&philo->forks[id + 1]);		
		if (death_detector(philo))
			return (1);
		print_status(philo, id, "has taken a fork on the left");
	}
	return (0);
}

static int	eating(t_philo *philo, int id)
{
	if (id % 2 == 0)
	{
		if (grab_fork(philo, id, RIGHT) || grab_fork(philo, id, LEFT))
			return (1);
	}
	else if (id % 2 == 1)
	{
		if (grab_fork(philo, id, LEFT) || grab_fork(philo, id, RIGHT))
			return (1);
	}
	philo->parr[id].status = EAT;
	print_status(philo, id, "is eating");
	usleep(philo->in.tteat * 1000);
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[id + 1]);
	gettimeofday(&philo->parr[id].fin_eat, NULL); // 마지막으로 먹은 시점 p에 기록
	return (0);
}

static int	sleeping(t_philo *philo, int id)
{
	if (death_detector(philo))
		return (1);
	philo->parr[id].status = SLEEP;
	print_status(philo, id, "is sleeping");
	usleep(philo->in.ttsleep * 1000);
	return (0);
}

static int	thinking(t_philo *philo, int id)
{
	if (death_detector(philo))
		return (1);
	philo->parr[id].status = THINK;
	print_status(philo, id, "is thinking");
	return (0);
}

void	*thread_func(t_philo *philo)
{
	int	id;

	id = philo->idx;
	// printf("쓰레드 생성: %d\n", id);
	gettimeofday(&philo->parr[id].fin_eat, NULL);
	id = philo->idx;
	while (philo->death == 0)
	{
		if (eating(philo, id))
			break;
		if (sleeping(philo, id))
			break;
		if (thinking(philo, id))
			break;
	}
	// printf("쓰레드 %d 죽음\n", id);
	return (0);
}