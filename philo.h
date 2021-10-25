#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_p
{
	struct	timeval starttime;
	struct	timeval currtime;
	double	timegap;
	char	status;

}	t_p;

typedef struct s_philo
{
	int				pnum;
	t_p				*parr;
	pthread_mutex_t	*forks;
}	t_philo;

#endif