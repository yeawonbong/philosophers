# include "philo.h"

int	term_detector(t_philo *philo)
{
	if (philo->death == 1 || \
	(0 < philo->in.eatnum && philo->in.eatnum < philo->ate_all))
		return (1);
	return (0);
}

static int full(t_philo *philo, int id)
{
	if (philo->parr[id].ate == philo->in.eatnum)
		philo->ate_all++;
	if (philo->ate_all == philo->in.eatnum)
	{
		pthread_mutex_lock(&philo->death_lock);
		philo->ate_all++;
		pthread_mutex_lock(&philo->print_lock);
		ft_putstr_fd("Philosophers finished dinning!\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

static int	starve(t_philo *philo, int id)
{
	if ((get_time_ms() - philo->parr[id].last_eat) > philo->in.ttdie)
	{
		pthread_mutex_lock(&philo->death_lock);
		// printf("%5lld ms Philosopher %2d died\n", get_time_ms() - philo->start, id + 1);
		print_status(philo, id, "died");
		philo->death = 1;
		return (1);
	}
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int			id;

	id = philo->idx;
	while (term_detector(philo) == 0)
	{
		if (starve(philo, id))
			break ;
		if (0 < philo->in.eatnum && full(philo, id))
			break ;
		usleep(10);
	}
	usleep(2500);
	pthread_mutex_unlock(&philo->term);
	return (0);
}
