#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define LEFT 'L'
# define RIGHT 'R'

typedef struct s_p
{
	pthread_t		t;
	pthread_t		m; //monitor
	pthread_mutex_t	eating;
	struct timeval	fin_eat;
	int				ate;
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
	int				idx;
	pthread_mutex_t	death_lock;	
	int				death;
	pthread_mutex_t	print_lock;
	int				ate_all;
	pthread_mutex_t	term;
}	t_philo;


int		init(int argc, char *argv[], t_philo *philo);
void	*thread_func(t_philo *philo);
void	*monitor(t_philo *philo);




/*
**	p_time.c
*/
long long	get_timegap(struct timeval start, struct timeval end);
void		*monitor(t_philo *philo);
int			death_detector(t_philo *philo);
void		ft_usleep(int time);
long long	get_time_ms(struct timeval time);

/*
** p_utils.c
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

void	unlock_forks(t_philo *philo);

void	print_status(t_philo *philo, int id, char *str);




#endif