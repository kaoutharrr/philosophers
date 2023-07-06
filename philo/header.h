/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:29:40 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/25 22:35:13 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\e[0;31m"	
# define YELLOW "\e[1;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN   "\033[0;36m"
# define WHITE  "\033[0;37m"



typedef	struct t_private
{
	pthread_mutex_t	*lock1;
	pthread_mutex_t lock;
	unsigned long	time;
	//struct timeval  start_time;
	int number_of_philos;
	int number_of_forks;
	int time_to_eat;
	int time_to_sleep;
	unsigned long	time_to_die;
	int	times_he_ate;
	unsigned long	last_time_he_ate;
	int number_of_meals;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_t	philo;
	int index;
	struct t_public *public;
} t_private;

typedef struct t_public
{
	t_private	*private;
}	t_public;
void	my_lock(char *flag, int index, unsigned long time, pthread_mutex_t  *lock);
void    eat(int index, unsigned long time, pthread_mutex_t *lock);
void    b_eat(int index, unsigned long time, pthread_mutex_t *lock);
void    ft_sleep(int index, unsigned long time, pthread_mutex_t *lock);
void    die(int index, unsigned long time, pthread_mutex_t *lock);
void    think(int index, unsigned long time, pthread_mutex_t *lock);
//void	my_lock(char *flag, int index, unsigned long time);
void	my_usleep(unsigned long time);
unsigned long get_time(struct timeval time1);

unsigned long	get_actual_time();
t_public	*fill_struct(int *args, int ac);
int	ft_init(int *args, int ac);
int	*ft_parse(int ac, char **av);
char	**ft_check(char **av);
int     ft_strlen_a(char *s);
int		*fill_arr(char **av);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		error(char *s);
void	process(int *args, int size);

#   endif