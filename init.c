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

void	mutexinit(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->pnum);
	i = 0;
	while (i < philo->pnum)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
	}
}

void	init(int argc, char *argv[], t_philo *philo)
{
	philo->pnum = atoi(argv[1]);
	philo->parr = malloc(sizeof(t_p) * philo->pnum);
	
}