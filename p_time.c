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

long long	get_timegap(struct timeval start)
{
	struct timeval	end;
	
	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

// int	main()
// {
// 	struct timeval start;
// 	pthread_t t1, t2;

// 	gettimeofday(&start, NULL);

// 	return (printf("timegap : %lld\n", get_timegap(start)));
// }