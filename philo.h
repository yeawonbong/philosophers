#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define EAT 'E'
# define SLEEP 'S'
# define THINK 'T'

typedef struct s_p
{
	pthread_t		t;
	pthread_t		m;
	char			status;
	struct timeval	fin_eat;

}	t_p;

typedef struct s_philo
{
	pthread_t		main_t;
	struct timeval	start;
	pthread_mutex_t	*forks;
	t_p				*parr;
	pthread_mutex_t	idx_lock;
	int				idx;
	int				pnum;
	int				mnum;
	pthread_mutex_t	mnum_lock;	
	long long		ttdie;
	long long		tteat;
	long long		ttsleep; // in microsec
	int				eatnum;
	int				death;
	int				ate_all;
	pthread_mutex_t	term;
}	t_philo;

/*
**	p_init.c
*/
int		isargs_digit(int argc, char *argv[]);
int		init_philo(int argc, char *argv[], t_philo *philo);
int		init_mutex(t_philo *philo);
int		init_pthread(t_philo *philo);
int		*init_monitor(t_philo *philo);///return type re
int		init(int argc, char *argv[], t_philo *philo);


/*
** p_threadfunc.c
*/
int		eating(t_philo *philo, int id);
int		sleeping(t_philo *philo, int id);
int		thinking(t_philo *philo, int id);
void	*thread_func(t_philo *philo);

/*
**	p_time.c
*/
long long	get_timegap(struct timeval start);
void		*monitor(t_philo *philo);
void		*terminator(t_philo *philo);

/*
** p_utils.c
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);






#endif