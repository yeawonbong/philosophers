# include "philo.h"

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

static int	starve(t_philo *philo, int id, struct timeval end)
{
	pthread_mutex_lock(&philo->parr[id].eating);
	pthread_mutex_unlock(&philo->parr[id].eating);
	if (get_timegap(philo->parr[id].fin_eat, end) >= philo->in.ttdie)
	{
		pthread_mutex_lock(&philo->print_lock);
		if (death_detector(philo) == 0)
			printf("%5lldms Philosopher %2d died\n", get_timegap(philo->start, end), id + 1);
		pthread_mutex_unlock(&philo->print_lock);
		philo->death = 1;
		pthread_mutex_unlock(&philo->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int	id;
	struct		timeval end;

	id = philo->idx;
	pthread_mutex_lock(&philo->m_lock);
	pthread_mutex_unlock(&philo->m_lock);
	while (death_detector(philo) == 0)
	{
		gettimeofday(&end, NULL);
		if (starve(philo, id, end))
			break ;
	}
	usleep(2500);
	pthread_mutex_unlock(&philo->term);
	return (0);
}


