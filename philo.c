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

void	*terminator(t_philo *philo)
{
	printf("=======terminator ON!\n");
	pthread_mutex_lock(&philo->term);
	usleep(300);
	printf("=======terminating!\n");
	pthread_mutex_unlock(&philo->term);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	t_term;
	int			status;

	status = 0;
	if (init(argc, argv, &philo))
		return (0);
	pthread_create(&t_term, NULL, (void*)terminator, &philo);
	pthread_join(t_term, NULL);
	usleep(100);

	// while(1){};
	return(0);
}