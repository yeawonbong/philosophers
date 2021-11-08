# include "philo.h"

/* to free

t_p *parr (스레드 포함되어있음)
pthread_mutex_t *forks;

// while (i < philo->pnum)
// 	pthread_detach(philo->parr[i++].t);
*/ 

void	unlock_forks(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->in.pnum)
	{
		pthread_mutex_unlock(&philo->forks[i]);
		pthread_mutex_destroy(&philo->forks[i++]);
	}
}

int	death_detector(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	// if (philo->death)
	// 	printf("DEATH DETECTION : %d\n", philo->death);
	if (philo->death == 1)
	{
		pthread_mutex_unlock(&philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_lock);
	return (0);
}

int	starve(t_philo *philo, int id)
{
	if (get_timegap(philo->parr[id].fin_eat) >= philo->in.ttdie \
		&& death_detector(philo) == 0 \
		&& philo->parr[id].status != EAT)
	{
		print_status(philo, id, "died");
		pthread_mutex_lock(&philo->death_lock);
		philo->death = 1;
		pthread_mutex_unlock(&philo->death_lock);
		unlock_forks(philo);
		return (1);
	}
	if (death_detector(philo))
		return (0);
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int	id;

	id = philo->idx;
	pthread_mutex_lock(&philo->m_lock);
	pthread_mutex_unlock(&philo->m_lock);
	while (death_detector(philo) == 0)
	{
		if (starve(philo, id))
			break ;
	}
	usleep(2500);
	pthread_mutex_unlock(&philo->term);
	return (0);
}


