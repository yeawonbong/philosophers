/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:13:50 by ybong             #+#    #+#             */
/*   Updated: 2021/11/17 17:14:17 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define RIGHT -1

typedef struct s_p
{
	pthread_t		t;
	long long		last_eat;
	int				ate;
}	t_p;

typedef struct s_input
{
	int				pnum;
	long long		ttdie;
	long long		tteat;
	long long		ttsleep;
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
	pthread_mutex_t	print_lock;
	pthread_mutex_t	exit;
}	t_philo;

/*
**	philo
*/
int			run(int argc, char *argv[], t_philo *philo);
void		*thread_func(t_philo *philo);
void		monitor(t_philo *philo);
int			print_status(t_philo *philo, int id, char *str);

/*
**	time_functions
*/
long long	get_time_ms(void);
void		ft_usleep(int time);

/*
**	utils
*/
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

#endif