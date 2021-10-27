/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:43:09 by ybong             #+#    #+#             */
/*   Updated: 2021/10/25 16:43:09 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(t_philo *philo)
{
	int	id;

	id = philo->idx;
	pthread_mutex_unlock(&philo->idx_lock);
	while (1)
	{
		if (get_timegap(philo->parr[id].fin_eat) > philo->ttdie)
		{
			printf("%lldms Philosopher %2d died\n", get_timegap(philo->start), id);
			// pthread_mutex_unlock(&philo->term);
			exit (0);
		}
	}
	return (philo);
}

// void	*terminator(t_philo *philo)
// {
// 	pthread_mutex_destroy(&philo->term);
// 	return (philo);
// }

int		main(int argc, char *argv[])
{
	t_philo	philo;
	int		status;

	status = 0;
	if (init(argc, argv, &philo))
		return (0);
	// pthread_mutex_destroy(&philo.term);
	return(0);
}