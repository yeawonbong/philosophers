#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define ODD 1
# define EVEN 0

typedef struct s_p
{
	pthread_t		t;
	pthread_t		m;
	char			status;
	struct	timeval	fin_eat;

}	t_p;

typedef struct s_philo
{
	struct timeval	start;
	pthread_mutex_t	idx_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	term;
	t_p				*parr;
	int				idx;
	int				pnum;
	int				ttdie;
	int				tteat;
	int				ttsleep; // in microsec
	int				eatnum;
	int				death;
}	t_philo;

/*
**	p_init.c
*/
void	init_forks(t_philo *philo);
void	init_philo(int argc, char *argv[], t_philo *philo);
void	init_pthread(t_philo *philo);
void	init(int argc, char *argv[], t_philo *philo);


/*
** p_threadfunc.c
*/
void	*eating(t_philo *philo, int id);
void	*sleeping(t_philo *philo, int id);
void	*thinking(t_philo *philo, int id);
void	*thread_func(t_philo *philo);

/*
**	p_time.c
*/
long long	get_timegap(struct timeval start);

/*
** p_utils.c
*/
int			ft_atoi(const char *str);


void	*monitor(t_philo *philo);




#endif