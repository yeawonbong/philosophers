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

static int	grab_fork(t_philo *philo, int id, int fork)
{
	if (fork < 0)
	{
		pthread_mutex_lock(&philo->forks[id]);
		if (print_status(philo, id, "has taken a fork"))
			return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[fork]);
		if (print_status(philo, id, "has taken a fork"))
			return (1);
	}
	return (0);
}

static int	eating(t_philo *philo, int id, int left)
{
	if (id % 2 == 0)
	{
		if (grab_fork(philo, id, left) || grab_fork(philo, id, RIGHT))
			return (1);
	}
	else if (id % 2 == 1)
	{
		if (grab_fork(philo, id, RIGHT) || grab_fork(philo, id, left))
			return (1);
	}
	philo->parr[id].last_eat = get_time_ms();
	if (print_status(philo, id, "is eating"))
		return (1);
	ft_usleep(philo->in.tteat);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[id]);
	if (++philo->parr[id].ate == philo->in.eatnum)
	{
		philo->ate_all++;
		return (1);
	}
	return (0);
}

static int	sleeping(t_philo *philo, int id)
{
	if (print_status(philo, id, "is sleeping"))
		return (1);
	ft_usleep(philo->in.ttsleep);
	if (print_status(philo, id, "is thinking"))
		return (1);
	return (0);
}

void	*thread_func(t_philo *philo)
{
	int	id;
	int	left;

	id = philo->idx;
	if (id == philo->in.pnum - 1)
		left = 0;
	else
		left = id + 1;
	philo->parr[id].last_eat = get_time_ms();
	while (1)
	{
		if (eating(philo, id, left))
			break ;
		if (sleeping(philo, id))
			break ;
	}
	return (0);
}
