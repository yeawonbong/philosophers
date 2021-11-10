/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:41:26 by ybong             #+#    #+#             */
/*   Updated: 2021/10/25 16:41:26 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// return((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return((time.tv_sec * 1000000) + (time.tv_usec));
}

void	ft_usleep(int time)
{
	long long		start;

	// usleep(time * 1000);
	start = get_time_ms();
	while (get_time_ms() < (start + time * 1000)){}
}