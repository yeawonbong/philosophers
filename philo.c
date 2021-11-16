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
static void	free_thread(t_philo *philo);

int	print_status(t_philo *philo, int id, char *str)
{
	if (term_detector(philo, id))
		return (1);
	pthread_mutex_lock(&philo->print_lock);
	// printf("%lld ms Philosopher %d %s\n", get_time_ms() - philo->start, id + 1, str);
		ft_putnbr_fd((get_time_ms() - philo->start) , STDOUT_FILENO);
		ft_putstr_fd(" ms Philosopher ", STDOUT_FILENO);
		ft_putnbr_fd(id + 1, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	pthread_mutex_unlock(&philo->print_lock);
	return (0);
}

static void	free_mutex(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_mutex_unlock(&philo->forks[i]);
		pthread_mutex_destroy(&philo->forks[i]);
		pthread_mutex_unlock(&philo->m_lock[i]);
		pthread_mutex_destroy(&philo->m_lock[i]);
		i++;
	}
	pthread_mutex_unlock(&philo->print_lock);
	pthread_mutex_unlock(&philo->exit);
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_destroy(&philo->exit);

	// while (i < philo->in.pnum)
	// {
	// 	pthread_mutex_unlock(&philo->forks[i]);
	// 	pthread_mutex_unlock(&philo->m_lock[i]);
	// 	i++;
	// }
	// pthread_mutex_unlock(&philo->print_lock);
	// pthread_mutex_unlock(&philo->exit);
	// free_thread(philo);
	// i = 0;
	// while (i < philo->in.pnum)
	// {
	// 	pthread_mutex_destroy(&philo->m_lock[i]);
	// 	pthread_mutex_destroy(&philo->forks[i]);
	// 	i++;
	// }
	// pthread_mutex_destroy(&philo->print_lock);
	// pthread_mutex_destroy(&philo->exit);
}

static void	free_thread(t_philo *philo)
{
	int	i;


	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_join(philo->parr[i].m, NULL);
		i++;
	}
	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_join(philo->parr[i].t, NULL);
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
	pthread_mutex_lock(&philo.exit);
	usleep(250);
	write(1, "fin\n", 4);
	free_mutex(&philo);
	write(1, "fin\n", 4);
	// free_thread(&philo);
	write(1, "fin\n", 4);
	return(0);
}
