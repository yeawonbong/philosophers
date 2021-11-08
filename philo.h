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
# define LEFT 'L'
# define RIGHT 'R'

typedef struct s_p
{
	pthread_t		t;
	pthread_t		m; //monitor
	char			status;
	struct timeval	fin_eat;
}	t_p;

typedef struct s_input
{
	int				pnum;
	long long		ttdie;
	long long		tteat;
	long long		ttsleep; // in microsec
	int				eatnum;
}	t_input;

typedef struct s_philo
{
	struct timeval	start;
	t_input			in;
	t_p				*parr;
	pthread_mutex_t	*forks;
	pthread_mutex_t m_lock;
	pthread_mutex_t	idx_lock;
	int				idx;
	pthread_mutex_t	death_lock;	
	int				death;
	pthread_mutex_t	print_lock;
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
// int		eating(t_philo *philo, int id);
// int		sleeping(t_philo *philo, int id);
// int		thinking(t_philo *philo, int id);
void	*thread_func(t_philo *philo);

/*
**	p_time.c
*/
long long	get_timegap(struct timeval start);
void		*monitor(t_philo *philo);
int			death_detector(t_philo *philo);

/*
** p_utils.c
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

void	unlock_forks(t_philo *philo);

void	print_status(t_philo *philo, int id, char *str);




#endif