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
	long long		last_eat;
	int				ate;
	pthread_mutex_t	eat_lock;
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
	long long		start;
	t_input			in;
	t_p				*parr;
	int				idx;
	int				death;
	int				ate_all;
	pthread_mutex_t	*forks;
	pthread_mutex_t m_lock;
	pthread_mutex_t	death_lock;	
	pthread_mutex_t	print_lock;
	pthread_mutex_t	term;
}	t_philo;


int		run(int argc, char *argv[], t_philo *philo);
void	*thread_func(t_philo *philo);
void	*monitor(t_philo *philo);
int		term_detector(t_philo *philo);
void	print_status(t_philo *philo, int id, char *str);

/*
**	p_time.c
*/
void		ft_usleep(int time);
long long	get_time_ms(void);

/*
** p_utils.c
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);






#endif