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