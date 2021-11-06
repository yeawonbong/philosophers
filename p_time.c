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

long long	get_time_ms(struct timeval time)
{
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_timegap(struct timeval start)
{
	struct timeval	end;
	
	gettimeofday(&end, NULL);
	return (get_time_ms(end) - get_time_ms(start));
}

void	ft_usleep(int time)
{
	struct timeval	tv;
	long long		start;

	gettimeofday(&tv, NULL);
	start = get_time_ms(tv);
	while (get_time_ms(tv) < (start + time))
	{
		usleep(100);
		gettimeofday(&tv, NULL);
	}
}