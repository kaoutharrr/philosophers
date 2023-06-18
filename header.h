/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:29:40 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/18 23:47:23 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED "\e[0;31m"	
# define YELLOW "\e[1;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN   "\033[0;36m"
# define WHITE  "\033[0;37m"

typedef struct t_data
{
    int size;
}           t_data;

int	*ft_parse(int ac, char **av, t_data *data);
char	**ft_check(char **av, t_data *data);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strlen_a(char *s);
int		*fill_arr(char **av);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		error(char *s);
void	process(int *args, int size);
char	**ft_split_join(char **av);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start,int len);
#   endif