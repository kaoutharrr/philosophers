/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:40:21 by kkouaz            #+#    #+#             */
/*   Updated: 2023/07/13 03:48:24 by kkouaz           ###   ########.fr       */
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
		my_lock("eat", private->index, private->time, &private->lock);
		pthread_mutex_lock(private->r_fork);
		my_lock("b_eat", private->index, private->time, &private->lock);
		pthread_mutex_lock(&private->lock);
			private->times_he_ate++;
		pthread_mutex_unlock(&private->lock);
		pthread_mutex_lock(&private->lock);
		private->last_time_he_ate = get_actual_time();
		pthread_mutex_unlock(&private->lock);
		my_usleep(private->time_to_eat);
		pthread_mutex_unlock(private->l_fork);
		pthread_mutex_unlock(private->r_fork);
		my_lock("sleep", private->index, private->time, &private->lock);
		my_usleep(private->time_to_sleep);
		my_lock("think", private->index, private->time, &private->lock);
		usleep(50);
	}
	return (NULL);
}

int	ft_init(int *args, int ac)
{
	t_public		*public;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	int				i;
	unsigned long	time;
	int				j;

	j = 0;
	i = 0;
	fork = malloc(args[0] * sizeof(pthread_mutex_t));
	philo = malloc(args[0] * sizeof(pthread_t));
	public = fill_struct(args, ac);
	i = 0;
	while (i < args[0])
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < args[0])
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
	while (i < args[0])
	{
		public->private[i].time = time;
		public->private[i].last_time_he_ate = get_actual_time();
		public->private[i].times_he_ate = 0;
		i++;
	}
	i = 0;
	while (i < args[0])
		pthread_mutex_init(&public->private[i++].lock, NULL);
	i = 0;
	while (i < args[0])
	{
		pthread_create(&public->private[i].philo, NULL, routine,
			&public->private[i]);
		usleep(50);
		i++;
	}
	while (1)
	{
		i = 0;
		j = 0;
		if (ft_finish(public->private, i, j, args))
			break ;
		usleep(50);
		i++;
	}
	return (0);
}

int	ft_finish(t_private *private, int i, int j, int *args)
{
	while (i < args[0])
	{
		pthread_mutex_lock(&private[i].lock);
		if (get_actual_time() - private[i].last_time_he_ate
			>= private[i].time_to_die)
		{
			pthread_mutex_unlock(&private[i].lock);
			my_lock("die", private[i].index, private[i].time, &private[i].lock);
			return (1);
		}
		pthread_mutex_unlock(&private[i].lock);
		if (private[i].number_of_meals != -1)
		{
			pthread_mutex_lock(&private[i].lock);
			if (private[i].times_he_ate >= private[i].number_of_meals)
			{
				pthread_mutex_unlock(&private[i].lock);
				j++;
			}
			pthread_mutex_unlock(&private[i].lock);
			if (j == args[0])
				return (1);
		}
	}
	return (0);
}

t_public	*fill_struct(int *args, int ac)
{
	t_public	*public;
	int			i;

	public = malloc(sizeof(t_public));
	public->private = malloc(args[0] * sizeof(t_private));
	i = 0;
	while (i < args[0])
	{
		public->private[i].time_to_die = args[1];
		public->private[i].time_to_eat = args[2];
		public->private[i].time_to_sleep = args[3];
		if (ac == 6)
			public->private[i].number_of_meals = args[4];
		else
			public->private[i].number_of_meals = -1;
		public->private[i].index = i;
		i++;
	}
	return (public);
}
