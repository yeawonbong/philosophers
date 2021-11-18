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

int	print_status(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(&philo->print_lock);
	if (philo->death == 1)
		return (1);
	// printf("%lld ms Philosopher %d %s\n", get_time_ms() - philo->start, id + 1, str);
	ft_putnbr_fd((get_time_ms() - philo->start), STDOUT_FILENO);
	ft_putstr_fd(" ms Philosopher ", STDOUT_FILENO);
	ft_putnbr_fd(id + 1, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	usleep(10);
	pthread_mutex_unlock(&philo->print_lock);
	return (0);
}

static void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_mutex_unlock(&philo->forks[i]);
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_unlock(&philo->print_lock);
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_unlock(&philo->exit);
	pthread_mutex_destroy(&philo->exit);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (run(argc, argv, &philo))
		return (0);
	monitor(&philo);
	pthread_mutex_lock(&philo.exit);
	free_all(&philo);
	usleep(2500);
	free(philo.parr);
	return (0);
}
