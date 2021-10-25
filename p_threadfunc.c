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
	pthread_mutex_lock(&philo->forks[philo->idx]);
	pthread_mutex_lock(&philo->forks[philo->idx + 1]);
	
}

void	*sleeping(t_philo *philo)
{

}

void	*sleeping(t_philo *philo)
{

}