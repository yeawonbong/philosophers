/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:41:26 by ybong             #+#    #+#             */
/*   Updated: 2021/10/25 16:41:26 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timegap(struct timeval start)
{
	struct timeval	end;
	
	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

void	*monitor(t_philo *philo)///return type re
{
	int	id;

	id = philo->idx;
	pthread_mutex_unlock(&philo->idx_lock);
	while (1)
	{
		if (philo->death || philo->ate_all)
		{
			pthread_mutex_lock(&philo->pnum_lock);
			if (--philo->pnum == 0)
				pthread_mutex_unlock(&philo->terminator);
			pthread_mutex_unlock(&philo->pnum_lock);
			return (NULL);
		}
		if (get_timegap(philo->parr[id].fin_eat) > philo->ttdie)
		{
			philo->death = 1;
			philo->pnum--;
			printf("%lldms Philosopher %2d died\n", get_timegap(philo->start), id);
			// pthread_mutex_unlock(&philo->term);
			return (NULL);
		}
	}
	return (0);
}

// void	*terminator(t_philo *philo)
// {
// 	while (1)
// 	{
// 		if (philo->death || philo->ate_all)
// 			return(NULL);
// 	}
// }

// int	main()
// {
// 	struct timeval start;
// 	pthread_t t1, t2;

// 	gettimeofday(&start, NULL);

// 	return (printf("timegap : %lld\n", get_timegap(start)));
// }