# include "philo.h"

int	term_detector(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	// if (philo->death)
	// 	printf("DEATH DETECTION : %d\n", philo->death);
	if (philo->death == 1 || \
	(0 < philo->in.eatnum && philo->in.eatnum < philo->ate_all))
	{
		pthread_mutex_unlock(&philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_lock);
	return (0);
}

static int full(t_philo *philo, int id)
{
	if (philo->parr[id].ate == philo->in.eatnum)
		philo->ate_all++;
	if (philo->ate_all == philo->in.eatnum)
	{
		philo->ate_all++;
		pthread_mutex_lock(&philo->print_lock);
		ft_putstr_fd("Philosophers finished dinning!\n", STDOUT_FILENO);
		pthread_mutex_unlock(&philo->print_lock);
		return (1);
	}
	return (0);
}

static int	starve(t_philo *philo, int id)
{
	// long long	gap;

	// pthread_mutex_lock(&philo->parr[id].eat_lock);
	if ((get_time_ms() - philo->parr[id].last_eat) >= philo->in.ttdie)
	{
		print_status(philo, id, " died\n");
		pthread_mutex_lock(&philo->death_lock);
		philo->death = 1;
		pthread_mutex_unlock(&philo->death_lock);
		// pthread_mutex_unlock(&philo->parr[id].eat_lock);
		return (1);
	}
	// pthread_mutex_unlock(&philo->parr[id].eat_lock);
	pthread_mutex_unlock(&philo->death_lock);
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int			id;

	id = philo->idx;
	pthread_mutex_lock(&philo->m_lock);
	pthread_mutex_unlock(&philo->m_lock);
	while (term_detector(philo) == 0)
	{
		if (starve(philo, id))
			break ;
		if (0 < philo->in.eatnum && full(philo, id))
			break ;
		usleep(10);
	}
	ft_usleep(2500);
	pthread_mutex_unlock(&philo->term);
	return (0);
}
