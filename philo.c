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

void	print_status(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(&philo->print_lock);
	if (term_detector(philo) == 0)
	{
		ft_putnbr_fd(get_time_ms() - philo->start, STDOUT_FILENO);
		ft_putstr_fd(" ms Philosopher ", STDOUT_FILENO);
		ft_putnbr_fd(id + 1, STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	pthread_mutex_unlock(&philo->print_lock);
}

static void	free_mutex(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_mutex_unlock(&philo->forks[i]);
		pthread_mutex_destroy(&philo->forks[i++]);
	}
	pthread_mutex_destroy(&philo->m_lock);
	pthread_mutex_destroy(&philo->death_lock);
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_destroy(&philo->term);
}

static void	free_thread(t_philo *philo)
{
	int	i;


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
	free(philo->parr);
}

int		main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	t_term;
	int			status;

	status = 0;
	if (run(argc, argv, &philo))
		return (0);
	pthread_mutex_lock(&philo.term);
	pthread_mutex_unlock(&philo.term);
	free_mutex(&philo);
	free_thread(&philo);
	return(0);
}
