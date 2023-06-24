/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:40:21 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/24 18:34:09 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *str)
{
	t_private *private;
	private = str;
	while (1)
	{
		pthread_mutex_lock(private->l_fork);
		printf("%lu philo %d took a fork\n", (get_actual_time() - private->time), private->index);
		pthread_mutex_lock(private->r_fork);
		printf("%lu philo %d took a fork\n", (get_actual_time() - private->time), private->index);
		pthread_mutex_lock(&private->lock);
		private->times_he_ate++;
		pthread_mutex_unlock(&private->lock);
		printf("%lu philo %d started eating\n", (get_actual_time() - private->time), private->index);
		pthread_mutex_lock(&private->lock);
		private->last_time_he_ate = get_actual_time();
		pthread_mutex_unlock(&private->lock);
		usleep(private->time_to_eat * 1000);
		pthread_mutex_unlock(private->l_fork);
		pthread_mutex_unlock(private->r_fork);
		printf("%lu philo %d is sleeping\n", (get_actual_time() - private->time), private->index);
		usleep(private->time_to_sleep * 1000);
		printf("%lu philo %d is thinking\n", (get_actual_time() - private->time), private->index);
	}
	return(NULL);
}

void	ft_init(int *args, int ac)
{
	t_public		*public;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t lock2;
	int				i;
	unsigned long	time;
	unsigned long  last;
	int j = 0;
	i = 0;
	fork = malloc(args[0] * sizeof(pthread_mutex_t ));	
	philo = malloc(args[0]  * sizeof(pthread_t ));
	public = fill_struct(args, ac);
	i = 0;
	while (i < args[0])
	{
		if(pthread_mutex_init(&fork[i], NULL) == -1)
			return ;
		i++;
	}
	i = 0;
	while(i < args[0])
	{
		public->private[i].l_fork = &fork[i];
		if (i == args[0] - 1)
			public->private[i].r_fork = &fork[0];
		else
			public->private[i].r_fork = &fork[i + 1];
		i++;
		}
	i = 0;
	time = get_actual_time();
	while(i < args[0])
	{
		public->private[i].time = time;
		public->private[i].last_time_he_ate = get_actual_time();
		public->private[i].times_he_ate = 0;
		i++;
	}
	i = 0;
	while(i < args[0])
	{
		pthread_mutex_init(&public->private[i].lock, NULL);
		i++;
	}
	pthread_mutex_init(&lock2, NULL);
	i = 1;
	while (i < args[0])
	{
		pthread_create(&public->private[i].philo, NULL, routine, &public->private[i]);
		usleep(50);
		i++;
	}
	i = 0;
	
	while(1)
	{
		i = 0;
		j = 0;
		while (i < args[0])
		{	
			pthread_mutex_lock(&public->private[i].lock);
			last = public->private[i].last_time_he_ate;
			pthread_mutex_unlock(&public->private[i].lock);
			if(get_actual_time() - last >= public->private[i].time_to_die)
			{
				pthread_mutex_lock(&lock2);
				printf("%lu philo %d died\n",get_actual_time() - time ,public->private[i].index);
				return;
			}
			if(public->private[i].number_of_meals != -1)
			{
				printf("laaaaaaaaa\n");
				pthread_mutex_lock(&public->private[i].lock);
				if(public->private[i].times_he_ate >= public->private[i].number_of_meals)
				{
					pthread_mutex_unlock(&public->private[i].lock);
					j++;
				}
				pthread_mutex_unlock(&public->private[i].lock);
				if(j == args[0] )
					return;
			}
			i++;
		}
	}
}

t_public	*fill_struct(int *args, int ac)
{
	t_public	*public;
	int			i;

	public = malloc(sizeof(t_public));
	public->private = malloc(args[0] *sizeof(t_private));
	i = 0;
	while(i < args[0])
	{
		public->private[i].time_to_die = args[1];
		public->private[i].time_to_eat = args[2];
		public->private[i].time_to_sleep = args[3];
		if(ac == 6)
			public->private[i].number_of_meals = args[4];
		else
			public->private[i].number_of_meals = -1;
		public->private[i].index = i;
		i++;
	}
	return(public);
}
	