# include "philo.h"

int	term_detector(t_philo *philo, int id)
{
	if (philo->death == 1)
		return (1);
	if (0 < philo->in.eatnum \
	 		&& philo->parr[id].ate == philo->in.eatnum)
		return (1);
	return (0);
}

static int full(t_philo *philo, int id)
{
	if (philo->death == 0 && philo->ate_all == philo->in.pnum)
	{
		pthread_mutex_lock(&philo->print_lock);
		ft_putstr_fd("Philosophers finished dinning!\n", STDOUT_FILENO);
		usleep(2500);
		pthread_mutex_unlock(&philo->exit);
		return (1);
	}
	return (0);
}

static int	starve(t_philo *philo, int id)
{
	if (philo->death == 0 && (get_time_ms() - philo->parr[id].last_eat) > philo->in.ttdie)
	{
		pthread_mutex_lock(&philo->print_lock);
		philo->death = 1;
		printf("%lld ms Philosopher %d died", (get_time_ms() - philo->start), id + 1);
		usleep(2500);
		pthread_mutex_unlock(&philo->exit);
		return (1);
	}
	return (0);
}

void	monitor(t_philo *philo)
{
	int			id;

	id = 0;
	
	while (1)
	{
		if (id == philo->idx)
			id = 0;
		if (starve(philo, id))
			break ;
		if (0 < philo->in.eatnum && full(philo, id))
			break ;
		id++;
	}
		// pthread_mutex_lock(&philo->print_lock);
		// printf("term!, monid: %d\n", id + 1);
		// pthread_mutex_unlock(&philo->print_lock);
}
