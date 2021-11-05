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
	int			i;

	i = 0;
	status = 0;
	if (init(argc, argv, &philo))
		return (0);
	// pthread_create(&t_term, NULL, (void*)terminator, &philo);
	// pthread_join(t_term, NULL);
	pthread_mutex_lock(&philo.term);
	printf("=======terminator ON!\n");
	sleep(3);
	while (i < philo.pnum)
	{
		pthread_join(philo.parr[i].t, NULL);
		i++;
	}
	i = 0;
	// while (i < philo.pnum)
	// {
	// 	pthread_join(philo.parr[i].m, NULL);
	// 	i++;
	// } join이 이상하다. thread 종료 기다려지지가 않는다. 
	printf("=======terminator OFF!\n");
	pthread_mutex_unlock(&philo.term);
	// while(1){};
	return(0);
}