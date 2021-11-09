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

static int	grab_fork(t_philo *philo, int id, int left, char c)
{
	if (c == RIGHT)
	{
		pthread_mutex_lock(&philo->forks[id]);
		if (term_detector(philo))
			return (1);
		print_status(philo, id, " has taken a fork on the right\n");
	}
	else if (c == LEFT)
	{
		pthread_mutex_lock(&philo->forks[left]);
		if (term_detector(philo))
			return (1);
		print_status(philo, id, " has taken a fork on the left\n");
	}
	return (0);
}

static int	eating(t_philo *philo, int id)
{
	int left;

	if (id == philo->in.pnum - 1)
		left = 0;
	else
		left = id + 1;
	if (id % 2 == 1)
	{
		if (grab_fork(philo, id, left, RIGHT) || grab_fork(philo, id, left, LEFT))
			return (1);
	}
	else if (id % 2 == 0)
	{
		if (grab_fork(philo, id, left, LEFT) || grab_fork(philo, id, left, RIGHT))
			return (1);
	}
	philo->parr[id].last_eat = get_time_ms();
	pthread_mutex_lock(&philo->parr[id].eat_lock);
	print_status(philo, id, " is eating\n");
	ft_usleep(philo->in.tteat);
	philo->parr[id].ate++;
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->parr[id].eat_lock);
	return (0);
}

static int	sleeping(t_philo *philo, int id)
{
	if (term_detector(philo))
		return (1);
	print_status(philo, id, " is sleeping\n");
	ft_usleep(philo->in.ttsleep);
	return (0);
}

static int	thinking(t_philo *philo, int id)
{
	if (term_detector(philo))
		return (1);
	print_status(philo, id, " is thinking\n");
	return (0);
}

void	*thread_func(t_philo *philo)
{
	int	id;

	id = philo->idx;
	philo->parr[id].last_eat = get_time_ms();
	while (philo->death == 0)
	{
		if (eating(philo, id))
			break;
		if (sleeping(philo, id))
			break;
		if (thinking(philo, id))
			break;
	}
	return (0);
}