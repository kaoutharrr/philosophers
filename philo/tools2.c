/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:33:14 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/24 18:27:31 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned long	get_actual_time()
{
	unsigned long	time;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return(time);
}

void	my_usleep(unsigned long time)
{
	unsigned long time_to_usleep;
	unsigned long i;
	i = 1;
	time_to_usleep = time / 10;
	while(i <= time_to_usleep)
	{
		usleep(10);
		i++;
	}
}