# include "philo.h"

int	term_detector(t_philo *philo, int id)
{
	if (philo->death == 1\
	 || (0 < philo->in.eatnum \
	 		&& philo->in.pnum < philo->ate_all))
	{
		return (1);
	}
	return (0);
}

static int full(t_philo *philo, int id)
{
	if (term_detector(philo, id))
		return (1);
	if (philo->parr[id].ate == philo->in.eatnum)
	{	
		// philo->parr[id].ate++;
		if (++philo->ate_all == philo->in.pnum)
		{
			pthread_mutex_lock(&philo->print_lock);
			philo->death = 1;
			ft_putstr_fd("Philosophers finished dinning!\n", STDOUT_FILENO);
			pthread_mutex_unlock(&philo->exit);
			return (1);
		}
		return (1);
	}
	return (0);
}

static int	starve(t_philo *philo, int id)
{
	if ((get_time_ms() - philo->parr[id].last_eat) > philo->in.ttdie * 1000)
	{
		if (term_detector(philo, id))
			return (1);
		philo->death = 1;
		pthread_mutex_lock(&philo->print_lock);
		usleep(2500);
		printf("%lld ms Philosopher %d died", (get_time_ms() - philo->start) / 1000, id + 1);
		pthread_mutex_unlock(&philo->exit);
		return (1);
	}
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int			id;

	id = philo->idx;
	pthread_mutex_lock(&philo->m_lock[id]);
	while (term_detector(philo, id) == 0)
	{
		if (starve(philo, id))
			break ;
		if (0 < philo->in.eatnum && full(philo, id))
			break ;
	}
	return (0);
}
