#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define ODD 1
# define EVEN 0

typedef struct s_p
{
	struct	timeval	fin_eat;
	double			timegap;
	char			status;

}	t_p;

typedef struct s_philo
{
	struct timeval	starttime;
	int				idx;
	int				pnum;
	int				ttdie;
	int				tteat;
	int				ttsleep; // in microsec
	int				eatnum;
	t_p				*parr;
	pthread_mutex_t	*forks;
}	t_philo;

/*
** threadfunc.c
*/
void	*eating(t_philo *philo);
void	*sleeping(t_philo *philo);
void	*thinking(t_philo *philo);
void	*thread_func(t_philo *philo);



#endif