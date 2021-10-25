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
	struct	timeval starttime;
	struct	timeval currtime;
	double	timegap;
	char	status;

}	t_p;

typedef struct s_philo
{
	int				idx;
	int				pnum;
	int				ttdie;
	int				tteat;
	int				ttsleep; // in microsec
	int				eatnum;
	t_p				*parr;
	pthread_mutex_t	*forks;
}	t_philo;

#endif