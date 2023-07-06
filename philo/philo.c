/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:40:21 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/25 22:36:05 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *str)
{
	t_private	*private;

	private = str;
	while (1)
	{
		pthread_mutex_lock(private->l_fork);
		my_lock("eat", private->index, private->time, private->lock1);
		pthread_mutex_lock(private->r_fork);
		my_lock("b_eat", private->index, private->time, private->lock1);
		pthread_mutex_lock(&private->lock);
			private->times_he_ate++;
		pthread_mutex_unlock(&private->lock);
		pthread_mutex_lock(&private->lock);
		private->last_time_he_ate = get_actual_time();
		pthread_mutex_unlock(&private->lock);
		my_usleep(private->time_to_eat);
		pthread_mutex_unlock(private->l_fork);
		pthread_mutex_unlock(private->r_fork);
		my_lock("sleep", private->index, private->time, private->lock1);
		my_usleep(private->time_to_sleep );
		my_lock("think", private->index, private->time, private->lock1);
	}
	return (NULL);
}

int	ft_init(int *args, int ac)
{
	t_public		*public;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t lock1;
	int				i;
	unsigned long	time;
	unsigned long  last;
	int j = 0;
	i = 0;
	 pthread_mutex_init(&lock1, NULL);

	fork = malloc(args[0] * sizeof(pthread_mutex_t ));	
	philo = malloc(args[0]  * sizeof(pthread_t ));
	public = fill_struct(args, ac);
	i = 0;
	while(i < args[0])
	{
		public->private[i].lock1 = &lock1;
		i++;
	}
	i = 0;
	while (i < args[0])
	{
		if(pthread_mutex_init(&fork[i], NULL) == -1)
			return (1);
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
	i = 0;
	while (i < args[0])
	{
		pthread_create(&public->private[i].philo, NULL, routine, &public->private[i]);
		usleep(50);
		i++;
	}
	i = 0;
	j = 0;
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
				my_lock("die" ,public->private[i].index, time,public->private[i].lock1) ;

				// i = 0;
				// while(i < args[0])
				// {
				// 	pthread_detach(public->private[i].philo);
				// 	i++;
				// }
				// pthread_mutex_lock(&lock2);
				// printf("%lu philo %d died\n",get_actual_time() - time ,public->private[i].index);
				return (1);
			}
			if(public->private[i].number_of_meals != -1)
			{
				pthread_mutex_lock(&public->private[i].lock);
				if(public->private[i].times_he_ate >= public->private[i].number_of_meals)
				{
					pthread_mutex_unlock(&public->private[i].lock);
					j++;
				}
				pthread_mutex_unlock(&public->private[i].lock);
				if(j == args[0] )
					return(1);
			}
			i++;
		}
		}
	return (0);
	// 	i = 0;
	// while(i < args[0])
	// {
	// 	pthread_detach(public->private[i].philo);
	// 	i++;
	// }
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

