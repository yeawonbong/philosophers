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

void	free_thread();
void	free_mutex();

void	print_status(t_philo *philo, int id, char *str)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	pthread_mutex_lock(&philo->print_lock);
	if (death_detector(philo) == 0)
		printf("%5lldms Philosopher %2d %s\n", get_timegap(philo->start, end), id + 1, str);
	pthread_mutex_unlock(&philo->print_lock);
}

static void	terminator(t_philo *philo)
{
	// printf("=======terminator ON!\n");
	int	i;

	pthread_mutex_lock(&philo->term);
	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_join(philo->parr[i].t, NULL);
		i++;
	}
	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_join(philo->parr[i].m, NULL);
		i++;
	}
	pthread_mutex_unlock(&philo->term);
	// printf("=======terminator OFF!\n");
}

int		main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	t_term;
	int			status;

	status = 0;
	if (init(argc, argv, &philo))
		return (0);
	terminator(&philo);
	unlock_forks(&philo);

	return(0);
}