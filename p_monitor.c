/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:53:46 by ybong             #+#    #+#             */
/*   Updated: 2021/11/17 17:19:45 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	full(t_philo *philo)
{
	if (philo->death == 0 && philo->ate_all == philo->in.pnum)
	{
		pthread_mutex_lock(&philo->print_lock);
		ft_putstr_fd("Philosophers finished dinning!\n", STDOUT_FILENO);
		usleep(2500);
		pthread_mutex_unlock(&philo->exit);
		return (1);
	}
	return (0);
}

static int	starve(t_philo *philo, int id)
{
	if (philo->death == 0 \
	&& (get_time_ms() - philo->parr[id].last_eat) > philo->in.ttdie)
	{
		pthread_mutex_lock(&philo->print_lock);
		philo->death = 1;
		printf("%lld ms Philosopher %d died", \
			(get_time_ms() - philo->start), id + 1);
		usleep(2500);
		pthread_mutex_unlock(&philo->exit);
		return (1);
	}
	return (0);
}

void	monitor(t_philo *philo)
{
	int	id;

	id = 0;
	while (philo->death == 0)
	{
		if (starve(philo, id))
			return ;
		if (0 < philo->in.eatnum && full(philo))
			return ;
		if (++id == philo->idx)
			id = 0;
	}
}
