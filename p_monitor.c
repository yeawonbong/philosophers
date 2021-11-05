# include "philo.h"

/* to free

t_p *parr (스레드 포함되어있음)
pthread_mutex_t *forks;

// while (i < philo->pnum)
// 	pthread_detach(philo->parr[i++].t);
*/ 

int	starve(t_philo *philo, int id)
{
	if (get_timegap(philo->parr[id].fin_eat) > philo->ttdie && philo->death == 0)
	{
		pthread_mutex_lock(&philo->death_lock);
		philo->death = 1;
		pthread_mutex_unlock(&philo->death_lock);
		printf("%5lldms Philosopher %2d died\n", get_timegap(philo->start), id);
		usleep(2500);
		pthread_mutex_unlock(&philo->term);
		return (1);
	}
	return (0);
}

void	*monitor(t_philo *philo)///return type re
{
	int	id;

	id = philo->idx;
printf("==모니터 %d 만들었다 함수 시작!!\n", id);
	pthread_mutex_unlock(&philo->idx_lock);
	pthread_mutex_lock(&philo->death_lock);
	while (philo->death == 0)
	{
		pthread_mutex_unlock(&philo->death_lock);
		if (starve(philo, id))
			break ;
	}
	printf("\n모니터 끝 ( %d ) \n\n", id);
	return (0);
}


